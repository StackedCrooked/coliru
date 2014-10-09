#include <atomic>
#include <cassert>
#include <cstddef>
#include <deque>
#include <functional>
#include <future>
#include <iostream>
#include <thread>




template <std::size_t N>
class stack_store
{
public:
    stack_store() = default;

    stack_store(stack_store const&) = delete;

    stack_store& operator=(stack_store const&) = delete;

    char* allocate(std::size_t n)
    {
        assert(pointer_in_buffer(ptr_) &&
               "stack_allocator has outlived stack_store");

        n = align(n);

        if (buf_ + N >= ptr_ + n)
        {
            auto r(ptr_);

            ptr_ += n;

            return r;
        }
        else
        {
            return static_cast<char*>(::operator new(n));
        }
    }

    void deallocate(char* const p, std::size_t n) noexcept
    {
        assert(pointer_in_buffer(ptr_)&&
        "stack_allocator has outlived stack_store");

        if (pointer_in_buffer(p))
        {
            n = align(n);

            if (p + n == ptr_)
            {
                ptr_ = p;
            }
            // else do nothing
        }
        else
        {
            ::operator delete(p);
        }
    }

    void reset() noexcept { ptr_ = buf_; }

    static constexpr ::std::size_t size() noexcept { return N; }

    ::std::size_t used() const {
        return ::std::size_t(ptr_ - buf_);
    }

private:
    static constexpr ::std::size_t align(::std::size_t const n) noexcept
    {
        return (n + (alignment - 1)) & -alignment;
    }

    bool pointer_in_buffer(char* const p) noexcept
    {
        return (buf_ <= p) && (p <= buf_ + N);
    }

private:
    static constexpr auto const alignment = alignof(std::max_align_t);

    char* ptr_ {buf_};

    alignas(std::max_align_t) char buf_[N];
};

template <class T, std::size_t N>
class stack_allocator
{
public:
    using store_type = stack_store<N>;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    using pointer = T* ;
    using const_pointer = T const* ;
    using reference = T& ;
    using const_reference = T const& ;
    using value_type = T;
    template <class U> struct rebind { using other = stack_allocator<U, N>; };

    stack_allocator() = default;
    stack_allocator(stack_store<N>& s) noexcept : store_(&s) { }
    template <class U>
    stack_allocator(stack_allocator<U, N> const& other) noexcept : store_(other.store_) { }

    stack_allocator& operator=(stack_allocator const&) = delete;

    T* allocate(::std::size_t const n)
    {
        std::cout << "allocate " << n << " " << typeid(T).name() <<  " size=" << sizeof(T) << std::endl;
        return static_cast<T*>(static_cast<void*>(
                                   store_->allocate(n * sizeof(T))));
    }

    void deallocate(T* const p, ::std::size_t const n) noexcept
    {
        std::cout << "Deallocate " << n << " " << typeid(T).name() <<  " size=" << sizeof(T) << std::endl;
        store_->deallocate(static_cast<char*>(static_cast<void*>(p)),
        n * sizeof(T));
    }

    template <class U, class ...A>
    void construct(U* const p, A&& ...args)
    {
        new(p) U(::std::forward<A>(args)...);
    }

    template <class U>
    void destroy(U* const p)
    {
        p->~U();
    }

    template <class U, std::size_t M>
    inline bool operator==(stack_allocator<U, M> const& rhs) const noexcept
    {
        return store_ == rhs.store_;
    }

    template <class U, std::size_t M>
    inline bool operator!=(stack_allocator<U, M> const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

private:
    template <class U, std::size_t M> friend class stack_allocator;
    store_type* store_ {};
};

template<typename T = char, std::size_t N>
stack_allocator<T, N> make_stack_allocator(stack_store<N>& store)
{
    return stack_allocator<T, N>(store);
}
template<typename T>
struct MoveOnCopy
{
    MoveOnCopy(){}

    explicit MoveOnCopy(T&& t) noexcept :
        mValue(std::move(t))
    {}

    MoveOnCopy(const MoveOnCopy& rhs):
        mValue(std::move(rhs.get()))
    {
    }

    MoveOnCopy& operator=(MoveOnCopy&& rhs)
    {
        mValue = std::move(rhs.get());
        return *this;
    }

    MoveOnCopy& operator=(const MoveOnCopy& rhs)
    {
        mValue = std::move(rhs.get());
        return *this;
    }

    T& operator*() const
    {
        return mValue;
    }

    T* operator->() const
    {
        return &mValue;
    }

    T& get() const
    {
        return mValue;
    }

    friend bool operator<(const MoveOnCopy<T>& lhs, const MoveOnCopy<T>& rhs)
    {
        return lhs.mValue < rhs.mValue;
    }

    mutable T mValue;
};


template<typename T, typename ...Args>
MoveOnCopy<T> MakeMoveOnCopy(Args&& ...args)
{
    return MoveOnCopy<T>(T(std::forward<Args>(args)...));
}



struct DispatchThingy
{
    DispatchThingy() :
        mQuit{false},
        mStorage(),
        mAllocator(mStorage),
      mDispatcherThread([=]{ dispatcher_thread(); })
    {
    }

    DispatchThingy(const DispatchThingy&) = delete;
    DispatchThingy& operator=(const DispatchThingy&) = delete;

    ~DispatchThingy()
    {
        mQuit = true;
        mDispatcherThread.join();
    }

    template<typename F>
    auto dispatch(F&& f) -> std::future<decltype(f())>
    {
        typedef decltype(f()) R;
        auto task = MakeMoveOnCopy<std::packaged_task<R()>>(std::allocator_arg, mAllocator, std::forward<F>(f));
        auto fut = task->get_future();
        mQueue.push_back([=]{ (*task)(); });
        return fut;
    }

private:
    void dispatcher_thread()
    {
        for (;!mQuit;)
        {
            while (!mQueue.empty())
            {
                std::cout << "Inside thread" << std::endl;
                mQueue.front()();
                std::cout << "/Inside thread" << std::endl;
                mQueue.pop_front();
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    }

    std::atomic<bool> mQuit;
    stack_store<2048> mStorage;
    stack_allocator<char, 2048> mAllocator;
    std::deque<std::function<void()>> mQueue;
    std::thread mDispatcherThread;
};



int main()
{
    DispatchThingy stack;
    auto f1 = stack.dispatch([=]() -> std::string { return "the first, "; });
    auto f2 = stack.dispatch([=]() -> std::string { return "the last, "; });
    auto f3 = stack.dispatch([=]() -> std::string { return "eternity."; });

    auto msg = f1.get();
    msg += f2.get();
    msg += f3.get();

    std::cout << msg << std::endl;

}
