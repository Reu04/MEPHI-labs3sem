#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

#include "Sequence.h"
#include "DynamicArray.h"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T>* object;
public:
    ArraySequence(T* items, size_t count);
    ArraySequence();
    ArraySequence(const DynamicArray<T>& obj);
    ArraySequence(const ArraySequence<T>& other);
    ArraySequence(ArraySequence<T>&& other);

    bool operator <(const ArraySequence<T>& other) const;
    bool operator >(const ArraySequence<T>& other) const;
    bool operator ==(const ArraySequence<T>& other) const;
    bool operator !=(const ArraySequence<T>& other) const;
    bool operator <=(const ArraySequence<T>& other) const;
    bool operator >=(const ArraySequence<T>& other) const;

    T GetFirst() const override;
    T GetLast() const override;
    T Get(int index) const override;
    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override;
    size_t GetLength() const override;

    void Append(T item) override;
    void Prepend(T item) override;
    void InsertAt(T item, int index) override;
    Sequence<T>* Concat(Sequence<T>* other) override;

    void Print(std::ostream& buff) const override;

    ~ArraySequence();
};
