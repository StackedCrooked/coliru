#include <array>
#include <cassert>
#include <type_traits>


// limited feature set (no clear, erase methods) makes it easier to not fuck up
template<typename T, unsigned Capacity>
class static_vector : private std::array<T, Capacity>
{
    typedef std::array<T, Capacity> Base;

public:
    static_vector() : Base(), size_() {}

    std::size_t capacity() const
    {
        return Capacity;
    }

    void push_back(const T& data)
    {
        assert(size_ < Capacity);
        (*this)[size_++] = data;
    }

    bool empty() const
    {
        return size() == 0;
    }

    std::size_t size() const
    {
        return size_;
    }

    void clear()
    {
        size_ = 0;
    }

    T& back()
    {
        assert(size_ > 0);
        return (*this)[size_ - 1];
    }

    const T& back() const
    {
        assert(size_ > 0);
        return (*this)[size_ - 1];
    }

    using Base::begin;
    using Base::cbegin;
    using Base::operator[];

    typedef typename Base::iterator iterator;
    typedef typename Base::const_iterator const_iterator;

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


