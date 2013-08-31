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
    
    T& back()
    {
        assert(size_ > 0);
        return (*this)[size() - 1];
    }
    
    T& front()
    {
        assert(size_ > 0);
        return *begin();
    }
    
    void pop_front()
    {
        std::move(begin() + 1, end(), begin());
        *end() = T();
        size_--;
    }
    
    void pop_back()
    {
        (*this)[size_--] = T();
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
    std::cout << "push_back: ";
    list.push_back(list.size());
    list.push_back(list.size());
    list.push_back(list.size());
    list.push_back(list.size());
    list.push_back(list.size());
    list.push_back(list.size());
    list.push_back(list.size());
    
    for (auto n : list)
    {
        std::cout << n << ' ';
    }
    
    std::cout << "\nfront=" << list.front() << std::endl;
    std::cout << "back=" << list.back() << std::endl;
    
    std::cout << "pop_back: ";
    list.pop_back();
    
    for (auto n : list)
    {
        std::cout << n << ' ';
    }
    
    std::cout << "\npop_front: ";
    list.pop_front();
    
    for (auto n : list)
    {
        std::cout << n << ' ';
    }
    
    std::cout << "\nresize: ";
    list.resize(list.size() / 2);
    
    for (auto n : list)
    {
        std::cout << n << ' ';
    }
}
