#include <memory>
#include <utility>
#include <iterator>
#include <cstddef>
#include <type_traits>
#include <tuple>

namespace detail
{
    using swallow = char[];
} // detail::

#define VARIADIC_EXPAND(expr) \
    (void)detail::swallow{ '\0', (void(expr), '\0')... }
    
template<int... Is> struct seq{ using type = seq; };
template<int I, int... Is>
struct gen_seq : gen_seq<I - 1, I - 1, Is...>{};
template<int... Is>
struct gen_seq<0, Is...> : seq<Is...>{};

template<class T>
struct gen_seq_for
    : gen_seq<std::tuple_size<typename std::remove_reference<T>::type>::value>{};

template<class T>
struct mystical_array
{
public:
    using size_type = std::size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    template<class U>
    mystical_array(std::initializer_list<U> il)
        : _size(il.size())
        , _buf(make_buf())
    {
        std::uninitialized_copy_n(il.begin(), _size, begin());
    }

    template<class... Us>
    mystical_array(Us&&... us)
        : _size(sizeof...(Us))
        , _buf(make_buf())
    {
        fill(gen_seq<sizeof...(Us)>{}, std::forward<Us>(us)...);
    }
    
    template<class... Tuples>
    mystical_array(std::piecewise_construct_t tag, Tuples&&... tuples)
        : _size(sizeof...(Tuples))
        , _buf(make_buf())
    {
        fill_piecewise(gen_seq<sizeof...(Tuples)>{}, std::forward<Tuples>(tuples)...);
    }
    
    size_type size() const noexcept { return _size; }
    
    bool empty() const noexcept { return _size == 0; }
    
    reference front() noexcept { return _buf[0]; }
    const_reference front() const noexcept { return _buf[0]; }
    
    reference back() noexcept { return _buf[_size - 1]; }
    const_reference back() const noexcept { return _buf[_size - 1]; }
    
    pointer data() noexcept { if (empty()) return nullptr; return &front(); }
    const_pointer data() const { if (empty()) return nullptr; return &front(); }
    
    reference operator[](size_type i) noexcept { return _buf[i]; }
    const_reference operator[](size_type i) const noexcept { return _buf[i]; }
    
    reference at(size_type i){ if (i >= _size) throw std::out_of_range("argument out of range"); return _buf[i]; }
    const_reference at(size_type i) const { if (i >= _size) throw std::out_of_range("argument out of range"); return _buf[i]; }
    
    iterator begin() noexcept { return data(); }
    const_iterator begin() const noexcept { return data(); }
    const_iterator cbegin() const noexcept { return begin(); }
    
    iterator end() noexcept { return begin() + _size; }
    const_iterator end() const noexcept { return begin() + _size; }
    const_iterator cend() const noexcept { return end(); }
    
    reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(end()); }
    const_reverse_iterator crbegin() const noexcept { return rbegin(); }
    
    reverse_iterator rend() noexcept { return rbegin() + _size; }
    const_reverse_iterator rend() const noexcept { return rbegin() + _size; }
    const_reverse_iterator crend() const noexcept { return rend(); }
    
private:
    T* make_buf(){ if (empty()) return nullptr; return (T*)::operator new(_size * sizeof(T)); };

    template<int... Is, class... Us>
    void fill(seq<Is...>, Us&&... us)
    {
        VARIADIC_EXPAND(
            ::new (static_cast<void*>(data() + Is)) T(std::forward<Us>(us))
        );
    }
    
    template<int... Is, class... Tuples>
    void fill_piecewise(seq<Is...>, Tuples&&... tuples)
    {
        VARIADIC_EXPAND(
            make_piecewise(gen_seq_for<Tuples>{}, Is, std::forward<Tuples>(tuples))
        );
    }
    
    template<int... Is, class Tuple>
    void make_piecewise(seq<Is...>, int i, Tuple&& tuple)
    {
        using std::get;
        ::new (static_cast<void*>(data() + i)) T(get<Is>(tuple)...);
    }

    size_type _size;
    std::unique_ptr<T[]> _buf;
};

#include <iostream>

int main()
{
    mystical_array<int> a1{1, 2, 3, 4, 5};
    mystical_array<int> a2{10., 20.f, 30l, 40ll, 50u};
    mystical_array<std::pair<int, int>> a3{ std::piecewise_construct, std::make_tuple(1,2), std::make_tuple(3,4) };
    
    for (auto&& e : a1)
        std::cout << e << " ";
    std::cout << "\n";
        
    for (auto&& e : a2)
        std::cout << e << " ";
    std::cout << "\n";
        
    for (auto&& e : a3)
        std::cout << "(" << e.first << ", " << e.second << ") ";
}