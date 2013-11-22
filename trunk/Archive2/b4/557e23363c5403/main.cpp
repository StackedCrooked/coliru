#include <iostream>
using namespace std;

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <memory>
#include <algorithm>
#include <utility>
#include <unordered_map>

template <typename Key, typename Data, typename Eq = std::equal_to<Key>>
class HashTable
{
public:

    struct Element
    {
        const Key key;
        const size_t hash;
        std::unique_ptr<Data> data;

    protected:

        friend class HashTable<Key, Data, Eq>;

        Element* next;

        Element() = delete;

        template <typename _Key>
        Element(size_t hash, _Key&& key) noexcept:
            key(std::forward<_Key>(key)),
            hash(hash),
            next(nullptr)
        {
        }

        Element(const Element&) = delete;
    };

private:

    typedef Element* Bucket;
    size_t numBuckets;
    Bucket* buckets;
    const Eq eq;
    size_t _size;

public:

    template <typename _Eq = Eq>
    HashTable(size_t initCapacity = 256, _Eq&& eq = _Eq()) noexcept:
        numBuckets(1 << static_cast<size_t>(ceil(log(static_cast<float>(initCapacity) * 4.f / 3.f) / log(2.f)))),
        buckets(new Bucket[numBuckets]),
        eq(std::forward<_Eq>(eq)),
        _size(0)
    {
        std::fill(buckets, buckets + numBuckets, nullptr);
    }

    ~HashTable()
    {
        clear();
        delete[] buckets;
    }

    void clear() noexcept
    {
        for (size_t i = 0; i < numBuckets; ++i)
        {
            Element* cur = buckets[i];
            while (cur)
            {
                Element* next = cur->next;
                delete cur;
                cur = next;
            }
            buckets[i] = nullptr;
        }
    }

    inline size_t size() const noexcept
    {
        return _size;
    }

private:
    inline Bucket& bucketFromHash(size_t hash) noexcept
    {
        return buckets[hash & (numBuckets - 1)];
    }
    inline bool load() noexcept
    {
        if (4 * _size >= 3 * numBuckets)
        {
            rehash();
            return true;
        }
        else
        {
            return false;
        }
    }
    void rehash() noexcept
    {
        auto oldBuckets = buckets;
        auto oldNumBuckets = numBuckets;
        numBuckets <<= 1;
        buckets = new Bucket[numBuckets];
        for (size_t i = 0; i < oldNumBuckets; ++i)
        {
            Element* old = oldBuckets[i];
            while (old)
            {
                Element* next = old->next;
                size_t hash = old->hash;
                Bucket& bucket = bucketFromHash(hash);
                Element* prev = nullptr;
                Element* cur = bucket;
                while (cur)
                {
                    Element& elt = *cur;
                    if (elt.hash < hash)
                    {
                        break;
                    }
                    prev = cur;
                    cur = cur->next;
                }
                if (!prev)
                {
                    old->next = bucket;
                    bucket = old;
                }
                else
                {
                    old->next = prev->next;
                    prev->next = old;
                }
                old = next;
            }
        }
        delete[] oldBuckets;
    }
public:

    template <typename _Key>
    Element& find_insert(size_t hash, _Key&& key) noexcept
    {
        Bucket& bucket = bucketFromHash(hash);
        Element* prev = nullptr;
        Element* cur = bucket;
        while (cur)
        {
            if (cur->hash == hash && eq(cur->key, key))
            {
                return *cur;
            }
            else if (cur->hash > hash)
            {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        ++_size;
        Element* next = new Element(hash, std::forward<_Key>(key));
        if (!prev)
        {
            bucket = next;
        }
        else
        {
            prev->next = next;
        }
        next->next = cur;
        load();
        return *next;
    }

    std::unique_ptr<Data> find_remove(size_t hash, const Key& key) noexcept
    {
        Bucket& bucket = bucketFromHash(hash);
        Element* prev = nullptr;
        Element* cur = bucket;
        while (cur)
        {
            if (cur->hash == hash && eq(cur->key, key))
            {
                std::unique_ptr<Data> ret = std::move(cur->data);
                if (prev)
                {
                    prev->next = cur->next;
                }
                else
                {
                    bucket = cur->next;
                }
                delete cur;
                --_size;
                return ret;
            }
            else if (cur->hash > hash)
            {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        return std::unique_ptr<Data>();
    }

    class const_iterator : public std::iterator<std::input_iterator_tag, const Data>
    {
    public:
        const HashTable<Key, Data, Eq>& table;
        mutable size_t bucketIndex;
        mutable const Element* bucket;
        size_t index;
        const_iterator(const HashTable<Key, Data, Eq>& table, size_t index) noexcept:
            table(table),
            bucketIndex(0),
            bucket(table.buckets[bucketIndex]),
            index(index)
        {
        }

        const_iterator(const const_iterator&) = default;
        const_iterator(const_iterator&&) = default;

        const_iterator& operator=(const const_iterator&) = default;
        const_iterator& operator++() noexcept
        {
            ++index;
            bucket = bucket->next;
            return *this;
        }
        bool operator==(const const_iterator& x) const noexcept
        {
            return x.index == index;
        }
        bool operator!=(const const_iterator& x) const noexcept
        {
            return x.index != index;
        }
        const Data& operator*() const noexcept
        {
            while (!bucket)
            {
                bucket = table.buckets[++bucketIndex];
            }
            return *bucket->data;
        }
        const Data& operator->() const noexcept
        {
            return this->operator*();
        }
    };

    const_iterator begin() const noexcept
    {
        return const_iterator(*this, 0);
    }
    const_iterator end() const noexcept
    {
        return const_iterator(*this, _size);
    }
};

#endif

int main()
{
    auto hashf = hash<int>();
    HashTable<int, array<int,1024>> table;
    unordered_map<int, unique_ptr<array<int,1024>>> map;
    for (size_t i = 0; i < 1024; ++i)
    {
        // find element with hash hashf(i) and key i. if not found, insert into hash.
        auto& loc = table.find_insert(hashf(i), i);
        if (!loc.data) loc.data.reset(new array<int,1024>);
        // and same for map
        auto& mloc = map[i];
        if (!mloc) mloc.reset(new array<int,1024>);
    }
    for (size_t i = 0; i < 1024; i += 10)
    {
        // find element in hash with hash hashf(i) and key i, removing it if found.
        auto arr = table.find_remove(hashf(i), i);
        if (arr)
        {
            // was removed, do something with it!
        }
        // and same for map
        auto ite = map.find(i);
        if (ite != map.end())
        {
            auto arr = std::move(*ite);
            map.erase(ite);
            // was removed, do something with it
        }
    }
    // I don't actually need iteration, I only implemented one for testing.
    for (const auto& arr: table) {}
    for (const auto& pair: map) { const auto& arr = *pair.second; }
    // I do need clearing.
    table.clear();
    map.clear();
    return 0;
}
