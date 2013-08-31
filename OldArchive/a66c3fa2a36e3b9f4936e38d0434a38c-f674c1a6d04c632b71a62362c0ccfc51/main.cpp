#include <array>
#include <cassert>
#include <iostream>

template<typename T, unsigned Capacity>
class StaticBuffer : private std::array<T, Capacity>
{
    typedef std::array<T, Capacity> Base;
public:
    StaticBuffer() : Base(), mSize() {}
    
    void resize(std::size_t inSize)
    {
        assert(inSize <= Capacity);
        mSize = inSize;
    }
    
    void push_back(const T& data)
    {
        assert(mSize < Capacity);
        (*this)[mSize++] = data;
    }
    
    void clear()
    {
        mSize = 0;
    }
    
    std::size_t size() const
    {
        return mSize;
    }
    
    typedef typename Base::iterator iterator;
    typedef typename Base::const_iterator const_iterator;
    
    using Base::begin;
    using Base::cbegin;
    
    iterator end()
    {
        return begin() + size();
    }
    
    const_iterator end() const
    {
        return begin() + size();
    }
    
    const_iterator cend() const
    {
        return begin() + size();
    }
    
    iterator erase(iterator first)
    {
        auto next = std::next(first);
        std::move(next, end(), first);
        --mSize;
        return first;
    }
    
private:
    unsigned mSize;
};

int main()
{
    StaticBuffer<int, 10> list;
    list.push_back(1);
    list.push_back(2);
    list.erase(list.begin());
    
    for (auto n : list)
    {
        std::cout << n << std::endl;
    }
}