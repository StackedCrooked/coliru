#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>


template<typename Key, typename T>
struct FlatMap
{
    void reserve(std::size_t new_capacity)
    {
        mKeys.reserve(new_capacity);
        mValues.reserve(new_capacity);
    }

    std::size_t capacity() const
    {
        return mKeys.capacity();
    }

    std::size_t size() const
    {
        return mKeys.size();
    }

    void insert(const Key& key, const T& value)
    {
        auto it = std::lower_bound(mKeys.begin(), mKeys.end(), key);
        auto offset_before_insert = std::distance(mKeys.begin(), it);
        mKeys.insert(it, key);
        mValues.insert(mValues.begin() + offset_before_insert, value);
    }

    T& at(const Key& key)
    {
        auto it = std::lower_bound(mKeys.begin(), mKeys.end(), key);
        auto offset = std::distance(mKeys.begin(), it);
        mKeys.insert(it, key);
        return *mValues.insert(mValues.begin() + offset, T());
    }

    struct iterator
    {
        explicit iterator(typename std::vector<Key>::iterator keyit, typename std::vector<T>::iterator valueit) : mKeyIt(keyit), mValueIt(valueit) { }

        iterator& operator++()
        { ++mKeyIt; ++mValueIt; return *this; }

        Key first()
        { return *mKeyIt; }

        T& second()
        { return *mValueIt; }

        friend bool operator==(iterator lhs, iterator rhs)
        { return lhs.mKeyIt == rhs.mKeyIt; }

        friend bool operator<(iterator lhs, iterator rhs)
        { return lhs.mKeyIt < rhs.mKeyIt; }

        typename std::vector<Key>::iterator mKeyIt;
        typename std::vector<T>::iterator mValueIt;
    };


    iterator find(Key key)
    {
        auto keyIt = std::lower_bound(mKeys.begin(), mKeys.end(), key);
        return iterator(keyIt, mValues.begin() + std::distance(keyIt - mKeys.begin()));
    }

    void erase(Key key)
    {
        auto it = std::lower_bound(mKeys.begin(), mKeys.end(), key);
        if (it == mKeys.end())
        {
            return;
        }
        auto offset = std::distance(mKeys.begin(), it);
        mKeys.erase(it);
        mValues.erase(mValues.begin() + offset);
    }

    void print()
    {
        auto index = 0;
        std::cout << "size=" << size() << ", cap=" << capacity() << ": {";
        assert(mKeys.size() == mValues.size());
        for (auto& key : mKeys)
        {
            if (index > 0)
            {
                std::cout << ", ";
            }

            std::cout << "{" << key << ", " << mValues.at(index++) << "}";

        }
        std::cout << "}" << std::endl;
    }

    std::vector<Key> mKeys;
    std::vector<T> mValues;
};



int main()
{
    FlatMap<int, char> map;
    map.print();

    map.at(7) = 'g'; map.print();
    map.at(6) = 'f'; map.print();
    map.at(5) = 'e'; map.print();
    map.at(4) = 'd'; map.print();
    map.at(3) = 'c'; map.print();
    map.at(2) = 'b'; map.print();
    map.at(1) = 'a'; map.print();

    map.erase(1); map.print();
    map.erase(2); map.print();
    map.erase(3); map.print();
    map.erase(4); map.print();
    map.erase(5); map.print();
    map.erase(6); map.print();
    map.erase(7); map.print();

}
