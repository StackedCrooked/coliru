#include <iterator>
#include <algorithm>
#include <memory>
#include <stdexcept>
#include <array>
#include <cstdint>
#include <cassert>

#ifdef _MSC_VER
#   define noexcept throw()
#endif

class dynarray_storage {
protected:
    dynarray_storage(std::size_t size) : _size(size) {
        if (_ptr >= std::end(_buffer) - _size) {
            throw std::bad_alloc();
        }
        _ptr += _size;
    }

    ~dynarray_storage() {
        _ptr -= _size;
    }

    void* allocated_ptr() {
        return _ptr - _size;
    }

private:
    size_t _size;

private:
    static std::uint8_t _buffer[10240];
    static std::uint8_t* _ptr;
};

std::uint8_t dynarray_storage::_buffer[10240];
std::uint8_t* dynarray_storage::_ptr = dynarray_storage::_buffer;

// The header <dynarray> defines a class template for storing sequences of objects where the size is fixed at construction. A dynarray supports random access iterators. An instance of dynarray<T> stores elements of type T. The elements of a dynarray are stored contiguously, meaning that if d is an dynarray<T> then it obeys the identity &d[n] == &d[0] + n for all 0 <= n < d.size().
// Unless otherwise specified, all dynarray operations have the same requirements and semantics as specified in 23.2.
// All operations except construction, destruction, and fill shall have constant-time complexity.
template <class T>
class dynarray : private dynarray_storage {
    // types:
    typedef       T                               value_type;
    typedef       T&                              reference;
    typedef const T&                              const_reference;
    typedef       T*                              pointer;
    typedef const T*                              const_pointer;
    typedef pointer                               iterator;       // See [container.requirements]
    typedef const_pointer                         const_iterator; // See [container.requirements]
    typedef std::reverse_iterator<iterator>       reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                        difference_type;

public:
    // [dynarray.cons] construct/copy/destroy:
    explicit dynarray(size_type c)
        : dynarray_storage(elem_size * c)
        , _ptr(static_cast<T *>(allocated_ptr()))
        , _size(c) {
        for (auto& elem : *this) {
            ::new(&elem) T;
        }
    }
    //template< typename Alloc >
    //    dynarray(size_type c, const Alloc& alloc);
    dynarray(size_type c, const T& v)
        : dynarray_storage(elem_size * c)
        , _ptr(static_cast<T *>(allocated_ptr()))
        , _size(c) {
        assert(c <= max_size());
        std::uninitialized_fill(_ptr, _ptr + c, v);
    }
    //template< typename Alloc >
    //    dynarray(size_type c, const T& v, const Alloc& alloc);
    //dynarray(const dynarray& d);
    //template< typename Alloc >
    //	dynarray(const dynarray& d, const Alloc& alloc);
    dynarray(std::initializer_list<T> l)
        : dynarray_storage(elem_size * l.size())
        , _ptr(static_cast<T *>(allocated_ptr()))
        , _size(l.size()) {
        assert(l.size() <= max_size());
        std::uninitialized_copy(l.begin(), l.end(), begin());
    }
    //template< typename Alloc >
    //	dynarray(initializer_list<T>, const Alloc& alloc);
    ~dynarray() {
        for (auto& elem : *this) {
            elem.~T();
        }
    }

    dynarray& operator=(const dynarray&) = delete;

    // iterators:
    iterator       begin()        noexcept{
        return iterator(data());
    }
        const_iterator begin()  const noexcept{
        return const_iterator(data());
    }
        const_iterator cbegin() const noexcept{
        return const_iterator(data());
    }
        iterator       end()          noexcept{
        return begin() + size();
    }
        const_iterator end()    const noexcept{
        return begin() + size();
    }
        const_iterator cend()   const noexcept{
        return cbegin() + size();
    }

        reverse_iterator       rbegin()        noexcept{
        return reverse_iterator(end());
    }
        const_reverse_iterator rbegin()  const noexcept{
        return const_reverse_iterator(cend());
    }
        const_reverse_iterator crbegin() const noexcept{
        return const_reverse_iterator(cend());
    }
        reverse_iterator       rend()          noexcept{
        return rbegin() + size();
    }
        const_reverse_iterator rend()    const noexcept{
        return rbegin() + size();
    }
        const_reverse_iterator crend()   const noexcept{
        return crbegin() + size();
    }

        // capacity:
        size_type size()     const noexcept{
        return _size;
    }
        size_type max_size() const noexcept{
        return _size;
    }
        bool      empty()    const noexcept{
        return size() != 0;
    }

        // element access:
        reference       operator[](size_type n) {
        assert(n >= 0 && n < size());
        return data()[n];
    }
    const_reference operator[](size_type n) const {
        assert(n >= 0 && n < size());
        return data()[n];
    }

    reference       front() {
        assert(size() > 0);
        return *begin();
    }
    const_reference front() const {
        assert(size() > 0);
        return *cbegin();
    }
    reference       back() {
        assert(size() > 0);
        return *rbegin();
    }
    const_reference back()  const {
        assert(size() > 0);
        return *crbegin();
    }

    reference       at(size_type n) {
        if (n < 0 || n >= size())
            throw std::length_error("at");
        return (*this)[n];
    }
    const_reference at(size_type n) const {
        if (n < 0 || n >= size())
            throw std::length_error("at");
        return (*this)[n];
    }

    // [dynarray.data] data access:
    T*       data()       noexcept{
        return _ptr;
    }
        const T* data() const noexcept{
        return _ptr;
    }

        // [dynarray.mutate] mutating member functions:
        void fill(const T& v) {
        std::fill(begin(), end(), v);
    }

private:
    value_type*		_ptr;
    size_type		_size;
    const static size_t elem_size = sizeof(T);
};

#include <string>
#include <vector>

int main() {
    for (int i = 0; i<10000; ++i) {
        dynarray<int> test(100, 10000);
    }
    try
    {
        dynarray<std::string> a(3, "aaaaa");
        {
            dynarray<std::string> b(2, "b");
            dynarray<std::string> c(3);
        }
        dynarray<std::string> d(3, "ddddd");
        {
            dynarray<std::string> e(10000000);
        }
    } catch (std::bad_alloc&) {
        for (int i = 0; i<10000; ++i) {
            dynarray<int> test(10);
        }
    }
}
