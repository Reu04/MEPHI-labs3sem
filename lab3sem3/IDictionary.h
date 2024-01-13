#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

#include "ArraySequence.h"
#include "Tuple.h"

template<typename TKey, typename TElement>
class IDictionary {
private:
    Sequence<Tuple<TKey, TElement>> Elements;
    size_t Size;
public:
    explicit IDictionary(size_t size) : Size(Size) {}

    size_t GetCount() const {
        return Elements.GetLength();
    }

    size_t GetSize() const {
        return Size;
    }

    TElement Get(const TKey& key) const {
        for (const auto& element : Elements) {
            if (element.First == key) {
                return element.Second;
            }
        }
        throw std::out_of_range("Key not found");
    }

    bool ContainsKey(const TKey& key) const {
        for (const auto& entry : Elements) {
            if (entry.First == key) {
                return true;
            }
        }
        return false;
    }

    void Add(const TKey& key, const TElement& element) {
        if (GetCount() < GetSize()) {
            if (!ContainsKey(key)) {
                Elements.Append(Tuple<TKey, TElement>(key, element));
            } else {
                throw std::invalid_argument("Key already exists");
            }
        } else {
            throw std::overflow_error("Dictionary is full");
        }
    }
};