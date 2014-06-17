#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>

template<typename T>
struct IndexerElem {
    IndexerElem() : occupied(false) {}

    IndexerElem(IndexerElem &&other) :
            occupied{other.occupied} {
        if(occupied) {
            new(&value) T{std::move(other.value)};
        } else {
            nextFree = other.nextFree;
        }
    }

    ~IndexerElem() {
        if(occupied) {
            value.~T();
        }
    }

    bool occupied;

    union {
        std::size_t nextFree;
        T value;
    };
};

template<typename T>
class Indexer {
public:
    typedef int index_t;

    template<typename U>
    index_t add(U &&val) {
        std::size_t idx;
        if(firstFree == badIndex()) {
            idx = storage.size();
            storage.push_back({});
        } else {
            idx = firstFree;
            firstFree = storage[idx].nextFree;
        }
        storage[idx].occupied = true;
        new(&storage[idx].value) T{std::forward<U>(val)};
        return idx;
    }

    T &get(index_t idx) {
        return storage[idx].value;
    }

    void remove(index_t idx) {
        assert(storage[idx].occupied);
        storage[idx].value.~T();
        storage[idx].occupied = false;
        storage[idx].nextFree = firstFree;
        firstFree = idx;
    }

private:
    static constexpr std::size_t badIndex() {
        return std::numeric_limits<std::size_t>::max();
    }

    std::vector<IndexerElem<T>> storage;
    std::size_t firstFree = badIndex();
};

int main() {
    Indexer<std::string> strings;

    auto print = [&strings] (int idx) {
        std::cout << idx << ": " << strings.get(idx) << "\n";
    };

    auto hi = strings.add("hi");
    auto other = strings.add("another one");

    print(hi);
    print(other);

    strings.remove(hi);

    print(other);

    auto reuse1 = strings.add("reuse?");
    print(reuse1);

    auto reuse2 = strings.add("sure!");
    print(reuse2);
    
    strings.remove(other);
    strings.remove(reuse2);
    
    auto reuse3 = strings.add("(trust me)");
    auto reuse4 = strings.add("(it really works)");
    
    print(reuse3);
    print(reuse4);
}