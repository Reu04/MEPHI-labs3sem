#pragma once

#include <cassert>

template<typename T>
struct ControlBlock { // Вспомогательный класс для объекта.
    T* Object_ = nullptr;
    size_t SharedCount_ = 0; // Счётчик ++ при каждом вызове либо оператора копирования, либо оператора присваивания.
    size_t WeakCount_ = 0;

    ControlBlock<T>(T* Object, size_t SharedCount, size_t WeakCount)
            : Object_(Object), SharedCount_(SharedCount), WeakCount_(WeakCount) {}

    ControlBlock& operator=(const ControlBlock& other) {
        assert(other.Object_ != nullptr && Object_ != nullptr);
        Object_ = other.Object_;
        SharedCount_ = other.SharedCount_;
        WeakCount_ = other.WeakCount_;
        return *this;
    }

    bool operator==(const ControlBlock& other) {
        assert(other.Object_ != nullptr || Object_ == nullptr);
        return Object_ == other.Object_;
    }

    bool operator!=(const ControlBlock& other) {
        return !(this == other);
    }
};

template<typename T>
class WeakPtr;

template<typename T>
class SharedPtr {
private:
    ControlBlock<T>* State_;

    friend class WeakPtr<T>;

    explicit SharedPtr<T>(ControlBlock<T>* State) : State_(State) { // для WeakPtr
        assert(State_ != nullptr);
        State_->SharedCount_++;
    }

public:
    explicit SharedPtr<T>(T* Object) {
        if (Object != nullptr) {
            State_ = new ControlBlock<T>(Object, 1, 0);
        } else {
            State_ = nullptr;
        }
    }

    SharedPtr<T>(const SharedPtr<T>& other) : State_(other.State_) {
        if (State_ != nullptr) {
            State_->SharedCount_++;
        }
    }

    SharedPtr<T>(SharedPtr<T>&& other) : State_(other.State_) {
        other.State_ = nullptr;
    }

    T& operator*() const {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        return *(State_->Object_);
    }

    /*
     * THE SAME:
     * obj->len() == (*obj).len() == obj.operator->()->len() == *(obj.operator->()).len()
     * obj-> == obj.State_->object->
     */
    T* operator->() const {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        return State_->Object_;
    }

    SharedPtr& operator=(const SharedPtr<T>& other) {
        assert(State_ != nullptr);
        State_->SharedCount_--;
        if ((State_->SharedCount_ + State_->WeakCount_ == 0) && (State_ != other.State_)) {
            delete State_;
        }
        State_ = other.State_;
        State_->SharedCount_++;
        return *this;
    }

    size_t UseCount() const {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        return State_->SharedCount_;
    }

    bool Unique() const {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        return State_->SharedCount_ == 1;
    }

    explicit operator bool() const {
        assert(State_ != nullptr);
        return State_->Object_ != nullptr;
    }

    T* Get() {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        return State_->Object_;
    }

    void Reset(T* newObject) {
        if (State_ != nullptr) {
            State_->SharedCount_--;
            if (State_->SharedCount_ + State_->WeakCount_ == 0) {
                delete State_->Object_;
                State_->Object_ = nullptr;
                delete State_;
                State_ = nullptr;
            }
        }
        if (newObject != nullptr) {
            State_ = new ControlBlock<T>(newObject, 1, 0);
        } else {
            State_ = nullptr;
        }
    }

    void Swap(SharedPtr<T>& other) {
        assert(State_ != nullptr && State_->Object_ != nullptr);
        std::swap(*State_->Object_, *other.State_->Object_);
    }

    ~SharedPtr<T>() {
        if (State_ != nullptr) {
            State_->SharedCount_--;
            if (State_->SharedCount_ + State_->WeakCount_ == 0) {
                delete State_->Object_;
                State_->Object_ = nullptr;
                delete State_;
                State_ = nullptr;
            }
        }
    }
};

template<typename T>
class WeakPtr {
private:
    ControlBlock<T>* State_;

public:
    explicit WeakPtr<T>(ControlBlock<T>* State): State_(State) {
        if (State != nullptr) {
            State_->WeakCount_++;
        }
    }

    WeakPtr<T>(const WeakPtr<T>& other) : State_(other->State_) {
        if (other->State_ != nullptr) {
            State_->WeakCount_++;
        }
    }

    SharedPtr<T> Lock() {
        if (State_ == nullptr) {
            return SharedPtr<T>(nullptr);
        }
        if (State_->Object_ == nullptr) {
            return SharedPtr<T>(nullptr);
        }
        return SharedPtr<T>(State_);
    }

    WeakPtr& operator=(const WeakPtr<T>& other) {
        if (State_ != nullptr) {
            State_->WeakCount_--;
            if (State_->SharedCount_ + State_->WeakCount_ == 0) {
                delete State_->Object_;
                State_->Object_ = nullptr;
                delete State_;
                State_ = nullptr;
            }
        }
        State_ = other.State_;
        if (State_ != nullptr) {
            State_->WeakCount_++;
        }
        return *this;
    }

    size_t UseCount() const {
        if (State_ == nullptr) {
            return 0;
        }
        return State_->SharedCount_;
    }

    bool Expired() const {
        return State_ == nullptr || State_->Object_ == nullptr;
    }

    ~WeakPtr() {
        if (State_ != nullptr) {
            State_->WeakCount_--;
            if (State_->SharedCount_ + State_->WeakCount_ == 0) {
                delete State_->Object_;
                State_->Object_ = nullptr;
                delete State_;
                State_ = nullptr;
            }
        }
    }
};