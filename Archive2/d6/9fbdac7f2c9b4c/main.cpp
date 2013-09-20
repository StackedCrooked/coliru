#include <cstddef>
#include <cassert>

template <std::size_t N>
class arena
{
    static const std::size_t alignment = 16;
    alignas(alignment) char buf_[N];
    char* ptr_;

    std::size_t 
    align_up(std::size_t n) noexcept
        {return (n + (alignment-1)) & ~(alignment-1);}

    bool
    pointer_in_buffer(char* p) noexcept
        {return buf_ <= p && p <= buf_ + N;}

public:
    arena() noexcept : ptr_(buf_) {}
    ~arena() {ptr_ = nullptr;}
    arena(const arena&) = delete;
    arena& operator=(const arena&) = delete;

    char* allocate(std::size_t n);
    void deallocate(char* p, std::size_t n) noexcept;

    static constexpr std::size_t size() {return N;}
    std::size_t used() const {return static_cast<std::size_t>(ptr_ - buf_);}
    void reset() {ptr_ = buf_;}
};

template <std::size_t N>
char*
arena<N>::allocate(std::size_t n)
{
    assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
    n = align_up(n);
    if (buf_ + N - ptr_ >= n)
    {
        char* r = ptr_;
        ptr_ += n;
        return r;
    }
    return static_cast<char*>(::operator new(n));
}

template <std::size_t N>
void
arena<N>::deallocate(char* p, std::size_t n) noexcept
{
    assert(pointer_in_buffer(ptr_) && "short_alloc has outlived arena");
    if (pointer_in_buffer(p))
    {
        n = align_up(n);
        if (p + n == ptr_)
            ptr_ = p;
    }
    else
        ::operator delete(p);
}

template <class T, std::size_t N>
class short_alloc
{
    arena<N>& a_;
public:
    typedef T value_type;

public:
    template <class _Up> struct rebind {typedef short_alloc<_Up, N> other;};

    short_alloc(arena<N>& a) noexcept : a_(a) {}
    template <class U>
        short_alloc(const short_alloc<U, N>& a) noexcept
            : a_(a.a_) {}
    short_alloc(const short_alloc&) = default;
    short_alloc& operator=(const short_alloc&) = delete;

    T* allocate(std::size_t n)
    {
        return reinterpret_cast<T*>(a_.allocate(n*sizeof(T)));
    }
    void deallocate(T* p, std::size_t n) noexcept
    {
        a_.deallocate(reinterpret_cast<char*>(p), n*sizeof(T));
    }

    template <class T1, std::size_t N1, class U, std::size_t M>
    friend
    bool
    operator==(const short_alloc<T1, N1>& x, const short_alloc<U, M>& y) noexcept;

    template <class U, std::size_t M> friend class short_alloc;
};

template <class T, std::size_t N, class U, std::size_t M>
inline
bool
operator==(const short_alloc<T, N>& x, const short_alloc<U, M>& y) noexcept
{
    return N == M && &x.a_ == &y.a_;
}

template <class T, std::size_t N, class U, std::size_t M>
inline
bool
operator!=(const short_alloc<T, N>& x, const short_alloc<U, M>& y) noexcept
{
    return !(x == y);
}

#include <vector>
#include <new>
#include <iostream>

std::size_t memory = 0;
std::size_t alloc = 0;

void* operator new(std::size_t s) // throw(std::bad_alloc)
{
    memory += s;
    ++alloc;
    return malloc(s);
}

void  operator delete(void* p) throw()
{
    --alloc;
    free(p);
}

void memuse()
{
    std::cout << "memory = " << memory << '\n';
    std::cout << "alloc = " << alloc << '\n';
}

int main()
{
    const unsigned N = 200;
    typedef short_alloc<int, N> Alloc;
    typedef std::vector<int, Alloc> SmallVector;
    arena<N> a;
    SmallVector v{Alloc(a)};
    v.push_back(1);
    memuse();
    v.push_back(2);
    memuse();
    v.push_back(3);
    memuse();
    v.push_back(4);
    memuse();
    for (auto i : v)
        std::cout << i << ' ';
    std::cout << '\n';
}