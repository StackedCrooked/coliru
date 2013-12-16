#include <iostream>
#include <array>


struct Functor // only supports signature `void()`
{
    template<typename F>
    Functor(F&& f) : base(new (&buf[0]) Fun<F>(std::forward<F>(f)))
    {        
        static_assert(sizeof(f) <= sizeof(buf), "");
        static_assert(std::alignment_of<F>::value <= std::alignment_of<SmallBuffer>::value, "");
    }
    
    Functor(Functor&& rhs) : buf(rhs.buf), base(rhs.base)
    {
        rhs.base = nullptr;
    }
    
    Functor& operator=(Functor&& rhs)
    {
        buf = rhs.buf;
        base = rhs.base;
        rhs.base = nullptr;
        return *this;
    }
    
    Functor(const Functor&) = delete;
    Functor& operator=(const Functor&) = delete;
    
    ~Functor()
    {
        if (base)
        {
            base->Base::~Base();
        }
    }
    
    void operator()() const
    {
        base->call();
    }
    
private:
    struct Base
    {
        virtual ~Base() {}
        virtual void call() const = 0;
    };
    
    template<typename F>
    struct Fun : Base, F
    {
        Fun(F&& f) : Base(), F(std::forward<F>(f)) {}
        
        void call() const override final
        {
            this->F::operator()();
        }
    };
    
    struct alignas(64) SmallBuffer : std::array<char, 128> {};
    SmallBuffer buf;    
    Base* base;
};

#include <chrono>
#include <functional>

int main()
{
    using namespace std::chrono;
    typedef high_resolution_clock Clock;
    
    {
        auto start_time = Clock::now();
        long a = 0;
        for (int i = 0; i != 100000000; ++i)
        {
            Functor([&]{ a++; })();
        }
        std::cout << duration_cast<microseconds>(Clock::now() - start_time).count() << std::endl;
    }
    
    {
        auto start_time = Clock::now();
        long a = 0;
        for (int i = 0; i != 100000000; ++i)
        {
            std::function<void()>([&]{ a++; })();
        }
        std::cout << duration_cast<microseconds>(Clock::now() - start_time).count() << std::endl;
    }
    
    {
        auto start_time = Clock::now();
        long a = 0;
        for (int i = 0; i != 100000000; ++i)
        {
            Functor([&]{ a++; })();
        }
        std::cout << duration_cast<microseconds>(Clock::now() - start_time).count() << std::endl;
    }
    
    {
        auto start_time = Clock::now();
        long a = 0;
        for (int i = 0; i != 100000000; ++i)
        {
            std::function<void()>([&]{ a++; })();
        }
        std::cout << duration_cast<microseconds>(Clock::now() - start_time).count() << std::endl;
    }
}

