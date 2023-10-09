#include <cassert>
#include <string>

template<typename T>
struct ControlBlock { // Вспомогательный класс для объекта.
    T* object_ = nullptr;
    size_t SharedCount = 0; // Счётчик ++ при каждом вызове либо оператора копирования, либо оператора присваивания.
    size_t WeakCount = 0;

    ControlBlock<T>(T* object, size_t sharedCount, size_t weakCount)
            : object_(object), SharedCount(sharedCount), WeakCount(weakCount) {}

    ControlBlock& operator=(const ControlBlock& other) {
        assert(other.object_ != nullptr && this->object_ != nullptr);
        this->object_ = other.object_;
        this->SharedCount = other.SharedCount;
        this->WeakCount = other.WeakCount;
    }

    bool operator==(const ControlBlock& other) {
        assert(other.object_ != nullptr || this->object_ == nullptr);
        if (object_ == other.object_) {
            return true;
        }
        return false;
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
    ControlBlock<T>* state_;

    friend class WeakPtr<T>;

    explicit SharedPtr<T>(ControlBlock<T>* state) : state_(state) { // для WeakPtr
        assert(state_ != nullptr);
        state_->SharedCount++;
    }

public:
    explicit SharedPtr<T>(T* object) {
        if (object != nullptr) {
            state_ = new ControlBlock<T>(object, 1, 0);
        } else {
            state_ = nullptr;
        }
    }

    SharedPtr<T>(const SharedPtr<T>& other) : state_(other.state_) {
        if (state_ != nullptr) {
            state_->SharedCount++;
        }
    }

    SharedPtr<T>(SharedPtr<T>&& other) : state_(other.state_) {

        other.state_ = nullptr;
    }

    T& operator*() const {
        assert(state_->object_ != nullptr);
        return *(state_->object_);
    }

    /*
     * THE SAME:
     * obj->len() == (*obj).len() == obj.operator->()->len() == *(obj.operator->()).len()
     * obj-> == obj.state_->object->
     */
    T* operator->() const {
        assert(state_->object_ != nullptr);
        return state_->object_;
    }

    SharedPtr& operator=(const SharedPtr<T>& other) {
        if ((--this->state_->SharedCount + this->state_->WeakCount == 0) && (state_ != other.state_)) {
            delete state_;
        }
        state_ = other.state_;
        state_->SharedCount++;
        return *this;
    }

    size_t Use_count() const {
        assert(state_->object_ != nullptr);
        return state_->SharedCount;
    }

    bool Unique() const {
        assert(state_->object_ != nullptr);
        return state_->SharedCount == 1;
    }

    explicit operator bool() const {
        return state_->object_ != nullptr;
    }

    T* Get() {
        assert(state_->object_ != nullptr);
        return state_->object_;
    }

    void Reset(T* newObject) {
        if (state_ != nullptr) {
            state_->SharedCount--;
            if (state_->SharedCount == 0) {
                delete state_->object_;
                state_->object_ = nullptr;
            }
            if (state_->SharedCount + state_->WeakCount == 0) {
                delete state_;
                state_ = nullptr;
            }
        }
        if (newObject != nullptr) {
            state_ = new ControlBlock<T>(newObject, 1, 0);
        } else {
            state_ = nullptr;
        }
    }

    void Swap(SharedPtr<T>& other) {
        std::swap(*state_->object_, *other.state_->object_);
    }

    ~SharedPtr<T>() {
        if (state_ != nullptr) {
            state_->SharedCount--;
            if (state_->SharedCount == 0) {
                delete state_->object_;
                state_->object_ = nullptr;
            }
            if (state_->SharedCount + state_->WeakCount == 0) {
                delete state_;
                state_ = nullptr;
            }
        }
    }
};

template<typename T>
class WeakPtr {
private:
    ControlBlock<T>* state_;

public:
    explicit WeakPtr<T>(ControlBlock<T>* state): state_(state) {
        if (state != nullptr) {
            state_->WeakCount++;
        }
    }

    WeakPtr<T>(const WeakPtr<T>& other) : state_(other->state_) {
        if (other->state_ != nullptr) {
            state_->WeakCount++;
        }
    }

    SharedPtr<T> Lock() {
        if (state_ == nullptr) {
            return SharedPtr<T>(nullptr);
        }
        if (state_->object_ == nullptr) {
            return SharedPtr<T>(nullptr);
        }
        return SharedPtr<T>(state_);
    }

    WeakPtr& operator=(const WeakPtr<T>& other) {
        if (state_ != nullptr) {
            state_->WeakCount--;
            if (state_->SharedCount + state_->WeakCount == 0) {
                delete state_;
                state_ = nullptr;
            }
        }
        state_ = other.state_;
        if (state_ != nullptr) {
            state_->WeakCount++;
        }
        return *this;
    }

    size_t Use_count() const {
        if (state_ == nullptr) {
            return 0;
        }
        return state_->SharedCount;
    }

    bool Expired() const {
        if (state_ == nullptr) {
            return true;
        }
        if (state_->object_ == nullptr) {
            return true;
        }
        return false;
    }
};