#include "DynamicArray.h"

template<typename T>
DynamicArray<T>::DynamicArray() : size_(1) {
    ptr_ = new T[size_];
}

template<typename T>
DynamicArray<T>::DynamicArray(size_t size) : size_(size) {
    ptr_ = new T[size];
}

template<typename T>
DynamicArray<T>::DynamicArray(T *items, size_t size) : size_(size) {
    ptr_ = new T[size];
    for (size_t i = 0; i < size; i++) {
        ptr_[i] = items[i];
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& other) : size_(other.size_) {
    ptr_ = new T[size_];
    for (size_t i = 0; i < other.size_; i++) {
        ptr_[i] = other.ptr_[i];
    }
}

template<typename T>
DynamicArray<T>::DynamicArray(DynamicArray &&other) : size_(other.size_), ptr_(other.ptr_) {
    other.size_ = 0;
    other.ptr_ = nullptr;
}

template<typename T>
DynamicArray<T>::DynamicArray(Iterator lhs, Iterator rhs) : size_(rhs - lhs) {
    ptr_ = new T[size_];
    for (int i = 0; i < size_; i++) {
        ptr_[i] = *(lhs++);
    }
}

//////////

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::begin() const {
    return Iterator(ptr_);
}

template<typename T>
typename DynamicArray<T>::Iterator DynamicArray<T>::end() const {
    return Iterator(ptr_ + size_);
}

template<typename T>
void DynamicArray<T>::Clear() {
    delete[] ptr_;
    ptr_ = nullptr;
    size_ = 0;
}

template<typename T>
T DynamicArray<T>::Get(int index) const {
    if (index >= (int) size_ || index < 0) {
        throw std::runtime_error("IndexOutOfRange");
    }
    return ptr_[index];
}

template<typename T>
size_t DynamicArray<T>::GetSize() const {
    return size_;
}

//////////

template<typename T>
void DynamicArray<T>::Resize(size_t newSize) {
    if (newSize == size_) {
        return;
    } else if (newSize > size_) {
        T *res = new T[newSize];
        for (size_t i = 0; i < size_; i++) {
            res[i] = ptr_[i];
        }
        delete[] ptr_;
        ptr_ = res;
        size_ = newSize;
    } else {
        T *res = new T[newSize];
        size_ = newSize;
        for (size_t i = 0; i < size_; i++) {
            res[i] = ptr_[i];
        }
        delete[] ptr_;
        ptr_ = res;
    }
}

template<typename T>
void DynamicArray<T>::Set(int index, T value) {
    if (index > (int) size_ || index < 0) {
        throw std::runtime_error("IndexOutOfRange");
    } else if (index < (int) size_) {
        ptr_[index] = value;
    } else { // if == size_
        Resize(size_ + 1);
        ptr_[index] = value;
    }
}

//////////

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray<T> &other) {
    size_ = other.size_;
    if (ptr_ != nullptr) {
        delete[] ptr_;
    }
    ptr_ = new T[other.size_];
    for (size_t i = 0; i < other.size_; i++) {
        ptr_[i] = other.ptr_[i];
    }
    return *this;
}

template<typename T>
T& DynamicArray<T>::operator[](const size_t &index) {
    return ptr_[index];
}

template<typename T>
T DynamicArray<T>::operator[](const size_t &index) const { // получение для const DynamicArray<T> object
    return ptr_[index];
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator+(const DynamicArray &other) {
    size_t index = size_;
    for (size_t i = 0; i < other.size_; i++) {
        Set(index, other.Get(i));
    }
    return *this;
}

template<typename T>
bool DynamicArray<T>::operator<(const DynamicArray &other) const { // лексикографическое сравнение
    for (size_t i = 0; i < std::min(size_, other.size_); i++) {
        if (ptr_[i] < other.ptr_[i]) {
            return true;
        }
        if (ptr_[i] > other.ptr_[i]) {
            return false;
        }
    }
    return GetSize() < other.GetSize();
}

template<typename T>
bool DynamicArray<T>::operator>(const DynamicArray &other) const {
    return other < *this;
}

template<typename T>
bool DynamicArray<T>::operator==(const DynamicArray &other) const {
    return !(*this < other) && !(*this > other);
}

template<typename T>
bool DynamicArray<T>::operator!=(const DynamicArray &other) const {
    return !(*this == other);
}

template<typename T>
bool DynamicArray<T>::operator<=(const DynamicArray &other) const {
    return (*this < other || *this == other);
}

template<typename T>
bool DynamicArray<T>::operator>=(const DynamicArray &other) const {
    return (*this > other || *this == other);
}

//////////

template<typename T>
void DynamicArray<T>::Print(std::ostream &buff) const {
    for (size_t i = 0; i < size_; i++) {
        buff << ptr_[i] << "\t";
    }
    buff << std::endl;
}

//////////

template<typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] ptr_;
}

template class DynamicArray<int>;
template class DynamicArray<double>;
template class DynamicArray<std::string>;
template class DynamicArray<char>;