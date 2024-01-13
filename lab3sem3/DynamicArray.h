#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <chrono>

template<typename T>
class DynamicArray {
private:
    size_t size_;
    T* ptr_;
public:
    class Iterator;

    DynamicArray();
    DynamicArray(size_t size);
    DynamicArray(T* items, size_t size);
    DynamicArray(const DynamicArray& other);
    DynamicArray(DynamicArray&& other);

    DynamicArray(Iterator lhs, Iterator rhs);

    class Iterator {
    private:
        friend class DynamicArray;
        T* curr_;
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* curr) : curr_(curr) {}
        Iterator() = default;
        Iterator(const Iterator& other) = default;
        Iterator(Iterator&& other) noexcept {
            curr_ = other.curr_;
            other.curr_ = nullptr;
        }

        ~Iterator() = default;

        reference operator*() const {
            return *curr_;
        }

        Iterator& operator++() { // prefix
            curr_++;
            return *this;
        }

        Iterator operator++(int) { // postfix
            auto temp = *this;
            ++(*this);
            return temp;
        }

        pointer operator->() const {
            return curr_;
        }

        Iterator& operator--() { // prefix
            --curr_;
            return *this;
        }

        Iterator operator--(int) {
            auto temp = *this;
            --(*this);
            return temp;
        }

        reference operator[](difference_type n) const {
            auto temp = curr_;
            return *(temp + n);
        }

        Iterator& operator+=(difference_type n) {
            curr_ += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            curr_ -= n;
            return *this;
        }

        Iterator operator+(difference_type n) {
            curr_ += n;
            return *this;
        }

        Iterator operator-(difference_type n) {
            curr_ -= n;
            return *this;
        }

        difference_type operator-(const Iterator& rhs) const {
            return curr_ - rhs.curr_;
        }

        Iterator& operator=(const Iterator& other) {
            curr_ = other.curr_;
            return *this;
        }

        bool operator==(const Iterator& rhs) const {
            return curr_ == rhs.curr_;
        }

        bool operator!=(const Iterator& rhs) const {
            return !(curr_ == rhs.curr_);
        }

        bool operator<(const Iterator& rhs) const {
            return curr_ < rhs.curr_;
        }

        bool operator>(const Iterator& rhs) const {
            return curr_ > rhs.curr_;
        }

        bool operator<=(const Iterator& rhs) const {
            return curr_ <= rhs.curr_;
        }

        bool operator>=(const Iterator& rhs) const {
            return curr_ >= rhs.curr_;
        }
    };

    Iterator begin() const;
    Iterator end() const;
    void Clear();

    T Get(int index) const;
    size_t GetSize() const;


    void Resize(size_t newSize);
    void Set(int index, T value);


    DynamicArray<T>& operator=(const DynamicArray<T>& other);
    T& operator [](const size_t& index);
    T operator [](const size_t& index) const;
    DynamicArray& operator +(const DynamicArray& other);
    bool operator <(const DynamicArray& other) const;
    bool operator >(const DynamicArray& other) const;
    bool operator ==(const DynamicArray& other) const;
    bool operator !=(const DynamicArray& other) const;
    bool operator <=(const DynamicArray& other) const;
    bool operator >=(const DynamicArray& other) const;

    void Print(std::ostream& buff) const;


    ~DynamicArray();
};