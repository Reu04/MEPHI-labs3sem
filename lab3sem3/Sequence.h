#pragma once

#include <iostream>
#include <string>
#include <cassert>
#include <vector>

template<typename T>
class Sequence {
public:
    virtual ~Sequence<T>() = default;

    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T>* GetSubsequence(int startIndex, int endIndex) const = 0;
    virtual size_t GetLength() const = 0;

    virtual void Append(T item) = 0;
    virtual void Prepend(T item) = 0;
    virtual void InsertAt(T item, int index) = 0;
    virtual Sequence<T>* Concat(Sequence<T>* other) = 0;

    virtual void Print(std::ostream& buff) const = 0;
};