#include <array>
#include <cassert>
#include <iostream>

template<typename T, unsigned Capacity>
class StaticBuffer : private std::array<T, Capacity>
{
    typedef std::array<T, Capacity> Base;
    
public:
    StaticBuffer() : Base(), size_() {}
    
    StaticBuffer(std::size_t size) : Base(), size_(size) {}
    
    void resize(std::size_t size)
    {   
        size_ = size;
        for (auto it = end(), e = Base::end(); it != e; ++it)
        {
            (*it) = T();
        }
    }
    
    void push_back(const T& data)
    {
        assert(size_ < Capacity);
        (*this)[size_++] = data;
    }
    
    void clear()
    {
        (*this) = Base();
        size_ = 0;
    }
    
    std::size_t size() const
    {
        return size_;
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
    
private:
    unsigned size_;
};

int main()
{
    StaticBuffer<int, 10> list;
    list.push_back(1);
    list.push_back(2);
    
    for (auto n : list)
    {
        std::cout << n << std::endl;
    }
}