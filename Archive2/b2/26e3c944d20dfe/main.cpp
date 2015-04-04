#include <boost/array.hpp>
#include <functional>
#include <map>
#include <set>
#include <stdexcept>
#include <atomic>
#include <cassert>
#include <iostream>
#include <typeinfo>
#include <vector>


template<typename F>
struct ScopeGuard
{
    ScopeGuard(F&& f) : mFunction(std::forward<F>(f)) { }

    // disable copy
    ScopeGuard(const ScopeGuard&) = delete;
    ScopeGuard& operator=(const ScopeGuard&) = delete;

    // enable move
    ScopeGuard(ScopeGuard&&) noexcept = default;
    ScopeGuard& operator=(ScopeGuard&&) noexcept = default;

    ~ScopeGuard()
    {
        if (mActive)
        {
            mFunction();
        }
    }

    void release()
    {
        mActive.release();
    }

private:
    F mFunction;

    struct Flag
    {
        Flag() : mFlag(true) {}

        Flag(Flag&& rhs) noexcept : mFlag(rhs.mFlag) { rhs.mFlag = false; }

        Flag& operator=(Flag&& rhs) noexcept
        {
            mFlag = rhs.mFlag;
            rhs.mFlag = false;
            return *this;
        }

        Flag(const Flag&) = default;
        Flag& operator=(const Flag&) = default;

        explicit operator bool() const { return mFlag; }

        void release() { mFlag = false; }

private:
        bool mFlag;
    };

    Flag mActive;
};


template<typename F>
inline ScopeGuard<F> make_scope_guard(F&& f)
{
    return ScopeGuard<F>(std::forward<F>(f));
}

struct TaggedPtr
{
    TaggedPtr() = default;

    explicit TaggedPtr(void* p) : data_(reinterpret_cast<uintptr_t>(p))
    {
    }

    uint16_t get_metadata() const { return data_ >> 48; }

    void set_metadata(uint16_t v)
    {
        uintptr_t ip = reinterpret_cast<uintptr_t>(get());
        ip |= static_cast<uintptr_t>(v) << 48;
        data_ = ip;
    }

    void* get() const
    {
        return reinterpret_cast<void*>(data_ & ((1ULL << 48) - 1));
    }

    friend bool operator==(TaggedPtr lhs, TaggedPtr rhs)
    {
        return lhs.get() == rhs.get();
    }

    uintptr_t data_;
};

boost::array<char, 150> storage;
std::atomic<int> storage_offset;


// Task size is only one pointer.
// Actual contents:
// - 48-bit pointer data
// - 16-bit index to storage
struct Task
{
    using FPtr = void (*) (void*);

    Task() = default;

    explicit Task(FPtr fptr, uint16_t storage_index) : fptr_(reinterpret_cast<void*>(fptr))
    {
        fptr_.set_metadata(storage_index);
    }

    void operator()()
    {
        if (!fptr_.get()) throw std::bad_function_call();
        uint16_t storage_index = fptr_.get_metadata();
        void* storage_ptr = &storage[storage_index];
        reinterpret_cast<FPtr>(fptr_.get())(storage_ptr);
    }

    TaggedPtr fptr_;
};


boost::array<Task, 100> tasks;
std::atomic<int> tasks_offset{0};



template<typename F>
uint16_t alloc(F&& f)
{
    static_assert(alignof(F) <= alignof(long), "");
    auto f_size = sizeof(std::pair<F, long>) - sizeof(long); // get aligned size

    int storage_in_use = storage_offset.fetch_add(f_size);
    if (storage_in_use + f_size > storage.size())
    {
        std::cout << " [!] (storage_in_use(" << storage_in_use << ") + f_size(" << f_size << ")) > storage.size(" << storage.size() << ")  => consume the queue!" << std::endl;
        auto num_tasks = static_cast<int>(tasks_offset);
        std::cout << "num_tasks=" << num_tasks << std::endl;
        for (auto b = tasks.begin(), e = b + num_tasks; b != e; ++b)
        {
            (*b)();
        }

        tasks_offset = 0;
        storage_offset = storage_in_use = 0;
        std::cout << " [*] All tasks are done." << std::endl << std::endl;

    }
    else
    {
        std::cout << " [+] Added task of size " << f_size << " to the queue." << std::endl;
    }
    auto memory = &storage[storage_in_use];
    new (memory) F(std::forward<F>(f));
    return storage_in_use;
}


template<typename F>
void post(F&& f)
{
    // hide the type information behind a
    // homogenous function pointer interface
    auto function_pointer = [](void* storage)
    {
        F& f = *static_cast<F*>(storage);
        auto destroy_on_scope_exit = make_scope_guard([&f] { f.~F(); });
        f();
    };

    tasks[tasks_offset++] = Task(function_pointer, alloc(std::forward<F>(f)));
}


void test_function() { std::cout << "test_function succeeded" << std::flush; }


struct Test
{
    Test()
    {
        assert(i == 123);
        std::cout << "Create Test " << this << std::endl;
    }

    Test(Test&& rhs)
    {
        assert(i == 123);
        std::cout << "Move-construct Test " << this << " from " << &rhs << std::endl;
    }

    Test& operator=(Test&&)
    {
        assert(i == 123);
        std::cout << "Move-assign Test " << this << std::endl;
        return *this;
    }

    Test(const Test&)
    {
        assert(i == 123);
        std::cout << "Copy Test " << this << std::endl;
    }

    Test& operator=(const Test&)
    {
        assert(i == 123);
        std::cout << "Copy-assign Test " << this << std::endl;
        return *this;
    }

    ~Test()
    {
        assert(i == 123);
        std::cout << "Destroy Test " << this << std::endl;
    }

    void operator()() const
    {
        assert(i == 123);
        std::cout << "Calling Test function call operator " << this << " i=" << i << std::endl;
    }

    int i = 123;
};


int main()
{
    post(Test());;


    for (auto b = tasks.begin(), e = tasks.begin() + tasks_offset; b != e; ++b)
    {
        auto& task = *b;
        try
        {
            task();
        }
        catch (const std::exception& e)
        {
            std::cout <<  "Caught " << e.what() << std::endl;
        }
    }
}
