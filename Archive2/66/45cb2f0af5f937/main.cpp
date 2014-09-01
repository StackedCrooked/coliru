#include <memory>
#include <utility>
#include <iterator>
#include <type_traits>
#include <tuple>
#include <initializer_list>
#include <cstddef>
#include <cassert>

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
    
struct capacity_t{ std::size_t value; };

template<class T>
struct mystical_array
{
    static_assert(!std::is_copy_constructible<T>{} && !std::is_move_constructible<T>{}, "use std::vector");
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

    template<class... Us>
    mystical_array(Us&&... us)
        : mystical_array(capacity_t{ sizeof...(Us) }, std::forward<Us>(us)...) {}
    
    template<class... Tuples>
    mystical_array(std::piecewise_construct_t tag, Tuples&&... tuples)
        : mystical_array(capacity_t{ sizeof...(Tuples) }, tag, std::forward<Tuples>(tuples)...) {}

    template<class... Us>
    mystical_array(capacity_t capacity, Us&&... us)
        : _size(sizeof...(Us))
        , _capacity(capacity.value)
        , _buf(make_buf())
    {
        assert(_size <= _capacity);
        fill(gen_seq<sizeof...(Us)>{}, std::forward<Us>(us)...);
    }
    
    template<class... Tuples>
    mystical_array(capacity_t capacity, std::piecewise_construct_t, Tuples&&... tuples)
        : _size(sizeof...(Tuples))
        , _capacity(capacity.value)
        , _buf(make_buf())
    {
        assert(_size <= _capacity);
        fill_piecewise(gen_seq<sizeof...(Tuples)>{}, std::forward<Tuples>(tuples)...);
    }
    
    mystical_array(mystical_array&&) = default;
    mystical_array(mystical_array const& other) = delete;
    
    ~mystical_array(){ while (!empty()) pop_back(); }
    
    mystical_array& operator=(mystical_array other){ swap(other); return *this; }
    
    void swap(mystical_array& other)
    {
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
        _buf.swap(other._buf);
    }
    
    size_type size() const noexcept { return _size; }
    size_type capacity() const noexcept { return _capacity; }
    bool empty() const noexcept { return _size == 0; }
    bool full() const noexcept { return _size == _capacity; }
    
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
    
    template<class... Args>
    void emplace_back(Args&&... args)
    {
        assert(!full());
        construct(_size++, std::forward<Args>(args)...);
    }
    
    void pop_back()
    {
        assert(!empty());
        destruct(--_size);
    }
    
    template<class InputIt>
    void append(InputIt first, InputIt last)
    {
        for (; first != last; ++first)
            emplace_back(*first);
    }
    
    template<class U>
    void append(std::initializer_list<U> il)
    {
        append(il.begin(), il.end());
    }
    
private:
    T* make_buf()
    {
        if (_capacity == 0)
            return nullptr;
        return (T*)::operator new(_capacity * sizeof(T));
    };
    
    struct deleter{ void operator()(void* ptr) const { ::operator delete(ptr); } };

    template<int... Is, class... Us>
    void fill(seq<Is...>, Us&&... us)
    {
        VARIADIC_EXPAND( construct(Is, std::forward<Us>(us)) );
    }
    
    template<int... Is, class... Tuples>
    void fill_piecewise(seq<Is...>, Tuples&&... tuples)
    {
        VARIADIC_EXPAND( make_piecewise(gen_seq_for<Tuples>{}, Is, std::forward<Tuples>(tuples)) );
    }
    
    template<int... Is, class Tuple>
    void make_piecewise(seq<Is...>, size_type i, Tuple&& tuple)
    {
        using std::get;
        construct(i, get<Is>(std::forward<Tuple>(tuple))...);
    }
    
    template<class... Args>
    void construct(size_type i, Args&&... args)
    {
        ::new (static_cast<void*>(data() + i)) T(std::forward<Args>(args)...);
    }
    
    void destruct(size_type i){ (data() + i)->~T(); }

    size_type _size, _capacity;
    std::unique_ptr<T[], deleter> _buf;
};

#include <iostream>

struct brick
{
    int value;
    explicit brick(int v) : value(v) {}
    brick(brick&&) = delete;
    brick(brick const&) = delete;
    brick& operator=(brick&&) = delete;
    brick& operator=(brick const&) = delete;
    ~brick() = default;
};

int main()
{
    mystical_array<brick> a1{1, 2, 3, 4, 5};
    mystical_array<std::pair<brick, brick>> a2{
        std::piecewise_construct,
        std::make_tuple(std::piecewise_construct, std::make_tuple(1), std::make_tuple(2)),
        std::make_tuple(std::piecewise_construct, std::make_tuple(3), std::make_tuple(4))
    };
    
    for (auto&& e : a1)
        std::cout << e.value << " ";
    std::cout << "\n";
        
    for (auto&& e : a2)
        std::cout << "(" << e.first.value << ", " << e.second.value << ") ";
    std::cout << "\n";
        
    mystical_array<brick> a3{ capacity_t{10}, 1, 2, 3, 4, 5 };
    mystical_array<std::pair<brick, brick>> a4{
        capacity_t{ 3 },
        std::piecewise_construct,
        std::make_tuple(std::piecewise_construct, std::make_tuple(1), std::make_tuple(2)),
        std::make_tuple(std::piecewise_construct, std::make_tuple(3), std::make_tuple(4))
    };
    
    a3.emplace_back(6);
    a3.append({7, 8, 9, 10});
    
    a4.emplace_back(std::piecewise_construct, std::make_tuple(5), std::make_tuple(6));
    
    for (auto&& e : a3)
        std::cout << e.value << " ";
    std::cout << "\n";
        
    for (auto&& e : a4)
        std::cout << "(" << e.first.value << ", " << e.second.value << ") ";
    std::cout << "\n";
}