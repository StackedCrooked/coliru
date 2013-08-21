#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>

namespace Nano
{

template <typename K, typename V> class unordered_map
{
    typedef std::unique_lock<std::recursive_mutex> raii_lock_t;

    std::unique_ptr<K[]> m_keys;
    std::unique_ptr<V[]> m_vals;
    std::recursive_mutex m_lock;
    std::size_t m_mask = 1;
    std::size_t m_size = 0;

    template <typename T>
    void lookup(T const& key, std::size_t& index)
    {
        std::size_t count = m_mask;

        while (std::not_equal_to<T>()(key, m_keys[index]))
        {
            if (--count == 0) { index = m_mask; break; }
            index = (index == m_mask - 1) ? 0 : index + 1;
        }
    }
    
    void rehash(std::size_t mask)
    {
        std::unique_ptr<K[]> keys (new K[mask]);
        std::unique_ptr<V[]> vals (new V[mask]);

        for (std::size_t prev = 0; prev < m_mask; ++prev)
        {
            if (m_keys[prev] && m_vals[prev])
            {
                std::size_t next = std::hash<K>()(m_keys[prev]) & (mask - 1);
                keys[next] = std::move(m_keys[prev]);
                vals[next] = std::move(m_vals[prev]);
            }
        }
        m_mask = mask;
        m_keys = std::move(keys);
        m_vals = std::move(vals);
    }

    public:

    inline void insert(K const& key, V&& val)
    {
        std::lock_guard<std::recursive_mutex> write (m_lock);

        if (m_size + 1 > (m_mask * 3) >> 2)
        {
            rehash(m_mask << 1);
        }

        std::size_t index = std::hash<K>()(key) & (m_mask - 1);
        lookup(key, index);

        if (index != m_mask)
        {
            m_size += 1;
            m_keys[index] = key;
            m_vals[index] = std::forward<V>(val);
        }
    }
    template <typename T>
    inline void remove(T const& key)
    {
        std::lock_guard<std::recursive_mutex> write (m_lock);
        std::size_t index = std::hash<T>()(key) & (m_mask - 1);
        lookup(key, index);

        if (index != m_mask)
        {
            m_size -= 1;
            m_keys[index] = nullptr;
            m_vals[index] = nullptr;
        }
    }
    inline raii_lock_t reader()
    {
        return raii_lock_t(m_lock);
    }
};

//------------------------------------------------------------------------------

template <typename K> class unordered_set
{
    typedef std::unique_lock<std::recursive_mutex> raii_lock_t;

    std::unique_ptr<K[]> m_keys;
    std::recursive_mutex m_lock;
    std::size_t m_mask = 1;
    std::size_t m_size = 0;

    template <typename T>
    void lookup(T const& key, std::size_t& index)
    {
        std::size_t count = m_mask;

        while (std::not_equal_to<T>()(key, m_keys[index]))
        {
            if (--count == 0) { index = m_mask; break; }
            index = (index == m_mask - 1) ? 0 : index + 1;
        }
    }
    
    void rehash(std::size_t mask)
    {
        std::unique_ptr<K[]> keys (new K[mask]);

        for (std::size_t prev = 0; prev < m_mask; ++prev)
        {
            if (m_keys[prev])
            {
                std::size_t next = std::hash<K>()(m_keys[prev]) & (mask - 1);
                keys[next] = std::move(m_keys[prev]);
            }
        }
        m_mask = mask;
        m_keys = std::move(keys);
    }

    public:

    inline void insert(K const& key)
    {
        std::lock_guard<std::recursive_mutex> write (m_lock);

        if (m_size + 1 > (m_mask * 3) >> 2)
        {
            rehash(m_mask << 1);
        }

        std::size_t index = std::hash<K>()(key) & (m_mask - 1);
        lookup(key, index);

        if (index != m_mask)
        {
            m_size += 1;
            m_keys[index] = key;
        }
    }
    template <typename T>
    inline void remove(T const& key)
    {
        std::lock_guard<std::recursive_mutex> write (m_lock);
        std::size_t index = std::hash<T>()(key) & (m_mask - 1);
        lookup(key, index);

        if (index != m_mask)
        {
            m_size -= 1;
            m_keys[index] = nullptr;
        }
    }
    inline raii_lock_t reader()
    {
        return raii_lock_t(m_lock);
    }
};

//------------------------------------------------------------------------------

template <typename T> class allocator : public std::allocator<T>
{
    public:

    typedef T* pointer_t;
    typedef T& reference_t;
    typedef T const* const_pointer_t;
    typedef T const& const_reference_t;
    typedef typename std::allocator<void>::pointer void_pointer_t;
    typedef typename std::allocator<void>::const_pointer const_void_pointer_t;

    explicit allocator() {}
   ~allocator() {}
    explicit allocator(allocator const&) {}
    template<typename U>
    explicit allocator(allocator<U> const&) {}

    pointer_t address(reference_t reference) { return &reference; }
    const_pointer_t address(const_reference_t reference) { return &reference; }

    pointer_t allocate(std::size_t n) const
    {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
    }
    pointer_t allocate(std::size_t n, const_void_pointer_t hint) const
    {
        return reinterpret_cast<T*>(::operator new(n * sizeof(T)));
    }
    
    std::size_t max_size() const
    { 
        return std::numeric_limits<std::size_t>::max() / sizeof(T);
    }

    void deallocate(pointer_t instance, std::size_t)
    { 
        ::operator delete(instance); 
    }

    template <typename U> struct rebind
    {
        typedef allocator<U> other;
    };
};

//------------------------------------------------------------------------------

typedef std::pair<std::uintptr_t, std::uintptr_t> delegate_key_t;

template <typename Re_t> class function;
template <typename Re_t, typename... Args> class function<Re_t(Args...)>
{
    typedef Re_t (*sig_t)(void*, Args...);

    void* m_this_ptr = nullptr;
    sig_t m_stub_ptr = nullptr;

    template <typename I, typename F>
    function (I&& this_ptr, F&& stub_ptr):
        m_this_ptr { std::forward<I>(this_ptr) },
        m_stub_ptr { std::forward<F>(stub_ptr) } {}

    public:

//------------------------------------------------------------------------------

    template <Re_t (*func_ptr)(Args...)>
    static inline function bind()
    {
        return { nullptr, [] (void *, Args... args) {
            return (*func_ptr)(args...); } };
    }
    template <typename T, Re_t (T::*meth_ptr)(Args...)>
    static inline function bind(T* pointer)
    {
        return { pointer, [] (void *this_ptr, Args... args) {
            return (static_cast<T*>(this_ptr)->*meth_ptr)(args...); } };
    }
    template <typename T, Re_t (T::*meth_ptr)(Args...) const>
    static inline function bind(T* pointer)
    {
        return { pointer, [] (void *this_ptr, Args... args) {
            return (static_cast<const T*>(this_ptr)->*meth_ptr)(args...); } };
    }

//------------------------------------------------------------------------------

    Re_t operator()(Args&&... args) const
    {
        return (*m_stub_ptr)(m_this_ptr, args...);
    }
    bool operator== (delegate_key_t const& other) const
    {
        return other == this->operator delegate_key_t();
    }
    bool operator!= (delegate_key_t const& other) const
    {
        return other != this->operator delegate_key_t();
    }
    bool operator== (function const& other) const
    {
        return other == this->operator delegate_key_t();
    }
    bool operator!= (function const& other) const
    {
        return other != this->operator delegate_key_t();
    }
    operator Nano::delegate_key_t() const
    {
        return { reinterpret_cast<std::uintptr_t>(m_this_ptr),
                 reinterpret_cast<std::uintptr_t>(m_stub_ptr) };
    }
};

} // namespace Nano ------------------------------------------------------------

class Foo
{
    Foo() = default;
};

namespace std // std::hash specializations
{

template <> struct hash<Foo>
{
    inline std::size_t operator()(Foo const& key) const
    {
        return reinterpret_cast<std::uintptr_t>(&key);
    }
};

template <> struct hash<Nano::delegate_key_t>
{
    inline std::size_t operator() (Nano::delegate_key_t const& key) const
    {
        return std::get<0>(key) ^ std::get<1>(key);
    }
};

template <typename T> struct hash<Nano::function<T>>
{
    inline std::size_t operator()(Nano::function<T> const& key) const
    {
        return std::hash<Nano::delegate_key_t>()(key);
    }
};

} // namespace std -------------------------------------------------------------

void print()
{
    std::cout << "Hello, World!" << std::endl;
}

int main()
{
    std::unordered_set<Foo> asdf;
    std::unordered_set<Nano::function<void()>> adsf;
    
    typedef Nano::function<void()> function;
    auto a = function::bind<print>();
    Nano::unordered_set<function> b;
    adsf.emplace(a);
    adsf.insert(a);
}
