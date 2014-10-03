#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>
#include <array>


template<typename Signature>
struct Function;


template<typename R, typename ...Args>
struct Function<R(Args...)>
{
    typedef Function<R(Args...)> this_type;

    Function() noexcept = delete;

    template<typename F>
    explicit Function(const F& f) noexcept
    {
        static_assert(sizeof(Impl<F>) <= sizeof(storage), "");
        new (&storage) Impl<F>(f);
    }

    Function(Function&& rhs) noexcept = delete;
    Function& operator=(Function&& rhs) noexcept = delete;

    Function(const Function& rhs) noexcept = delete;
    Function& operator=(const Function& rhs) noexcept = delete;

    ~Function() noexcept { base().~Base(); }

    R operator()(Args&& ...args) const noexcept
    {
        return base().call(std::forward<Args>(args)...);
    }

private:
    struct Base
    {
        virtual ~Base() noexcept {}
        virtual R call(const Args& ...args) const noexcept = 0;
    };

    template<typename F>
    struct Impl : Base
    {
        Impl(const F& f) noexcept  : f(f) {}

        virtual R call(const Args& ...args) const noexcept override final
        { return f(args...); }

        F f;
    };

    const void* data() const noexcept
    { return static_cast<const void*>(&storage); }

    const Base& base() const noexcept
    { return *static_cast<const Base*>(data()); }

    typedef std::array<uint64_t, STORAGE_SIZE + 1> Storage;
    alignas(alignof(uint64_t)) Storage storage;
};



#include <deque>
#include <iostream>
#include <chrono>


const int64_t num_iterations = 10 * 1000;
int64_t total_sum = 0;

volatile char storage[STORAGE_SIZE];


template<typename Task>
void test_fast()
{
    auto now = []{ return std::chrono::high_resolution_clock::now(); };

    int64_t sum = 0;
    
    // Note: store pointer because we don't want object size to influence the cost of insertion and iteration
    
    std::deque<Task> queue;

    auto t1 = now();

    for (long i = 0; i != num_iterations; ++i)
    {
        queue.emplace_back([=]() noexcept { return storage[i % sizeof(storage)]; });
    }

    auto t2 = now();

    for (auto&& task : queue) sum += task();

    auto t3 = now();

    using namespace std::chrono;
    std::cout
        << " alloc=" << duration_cast<microseconds>(t2 - t1).count() << "us"
        << "  call=" << duration_cast<microseconds>(t3 - t2).count() << "us"
        << " total=" << duration_cast<microseconds>(t3 - t1).count() << "us"
        << std::endl;
    total_sum += sum;
}


#include <functional>


void run()
{
    typedef Function<int()> MyFunction;
    std::cout << " MyFunction: ";
    test_fast<MyFunction>();
    
    auto copy = total_sum;
    total_sum = 0;

    typedef std::function<int()> StdFunction;
    std::cout << "StdFunction: ";
    test_fast<StdFunction>();
    std::cout << std::endl;
    
    assert(copy == total_sum);
}


int main()
{
    run();
    
    // prevent optimization
    return total_sum;
}