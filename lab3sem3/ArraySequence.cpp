#include <iostream>
#include <string>
#include <vector>

#include "ArraySequence.h"

template<typename T>
ArraySequence<T>::ArraySequence(T* items, size_t count) {
    object = new DynamicArray(items, count);
}

template<typename T>
ArraySequence<T>::ArraySequence(const DynamicArray<T>& obj) { // Нужно для Concat (для этого надо перегрузить =)
    *object = obj;
}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) {
    object = new DynamicArray<T>(*other.object);
}

template<typename T>
ArraySequence<T>::ArraySequence(ArraySequence<T>&& other) {
    object = new DynamicArray<T>(*other.object);
}

//////////

template<typename T>
bool ArraySequence<T>::operator <(const ArraySequence<T>& other) const { // лексикографическое сравнение
    for (size_t i = 0; i < std::min(object->GetSize(), other.object->GetSize()); i++) {
        if (object->Get(i) < other.object->Get(i)) {
            return true;
        }
        if (object->Get(i) > other.object->Get(i)) {
            return false;
        }
    }
    return object->GetSize() < other.object->GetSize();
}

template<typename T>
bool ArraySequence<T>::operator >(const ArraySequence<T>& other) const {
    return other < *this;
}

template<typename T>
bool ArraySequence<T>::operator ==(const ArraySequence<T>& other) const {
    return !(*this < other) && !(*this > other);
}

template<typename T>
bool ArraySequence<T>::operator !=(const ArraySequence<T>& other) const {
    return !(*this == other);
}

template<typename T>
bool ArraySequence<T>::operator <=(const ArraySequence<T>& other) const {
    return (*this < other || *this == other);
}

template<typename T>
bool ArraySequence<T>::operator >=(const ArraySequence<T>& other) const {
    return (*this > other || *this == other);
}

//////////

template<typename T>
T ArraySequence<T>::GetFirst() const {
    return object->Get(0);
}

template<typename T>
T ArraySequence<T>::GetLast() const {
    return object->Get(object->GetSize() - 1);
}

template<typename T>
T ArraySequence<T>::Get(int index) const {
    return object->Get(index);
}

template<typename T>
Sequence<T>* ArraySequence<T>::GetSubsequence(int startIndex, int endIndex) const {
    if (startIndex < 0 || endIndex < 0 || startIndex > object->GetSize() || endIndex > object->GetSize()) {
        throw std::runtime_error("IndexOutOfRange");
    }
    size_t size = endIndex - startIndex + 1;
    T* arr = new T[size];
    size_t index = 0;
    for (size_t i = startIndex; i <= endIndex; i++) {
        arr[index] = object->Get(i);
        index++;
    }
    Sequence<T>* res = new ArraySequence(arr, size);
    return res;
}

template<typename T>
size_t ArraySequence<T>::GetLength() const {
    return object->GetSize();
}

//////////

template<typename T>
void ArraySequence<T>::Append(T item) {
    object->Set(object->GetSize(), item);
}

template<typename T>
void ArraySequence<T>::Prepend(T item) {
    object->Set(0, item);
}

template<typename T>
void ArraySequence<T>::InsertAt(T item, int index) {
    object->Set(index, item);
}

template<typename T>
Sequence<T>* ArraySequence<T>::Concat(Sequence<T>* other) {
    auto* temp = new ArraySequence<T>(*dynamic_cast<ArraySequence<T>*>(other));
    T* arr = new T[GetLength() + temp->GetLength()];
    size_t size = GetLength() + temp->GetLength();
    for (size_t i = 0; i < GetLength(); i++) {
        arr[i] = object->Get(i);
    }
    for (size_t i = 0; i < temp->GetLength(); i++) {
        arr[GetLength() + i] = temp->object->Get(i);
    }

    auto* res = new ArraySequence<T>(arr, size);
    delete temp;
    return res;
}

//////////

template<typename T>
void ArraySequence<T>::Print(std::ostream& buff) const {
    object->Print(std::cout);
}

//////////

template<typename T>
ArraySequence<T>::~ArraySequence() {
    delete object;
}

template class ArraySequence<int>;
template class ArraySequence<double>;
template class ArraySequence<std::string>;
template class ArraySequence<char>;