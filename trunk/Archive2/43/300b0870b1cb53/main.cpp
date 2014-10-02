#include <chrono>
#include <iostream>


namespace test
{
    struct Int64
    {
        Int64() noexcept : value_() {}
        Int64(const Int64&) noexcept = default;
        Int64& operator=(const Int64&) noexcept = default;
        Int64(int64_t n) noexcept : value_(n) {}
        Int64& operator=(int64_t n) noexcept { value_ = n; return *this; }
        operator int64_t() const noexcept { return value_; }
        int64_t value_;
    };
}
    

namespace std
{   
    template<class T>
    struct common_type<test::Int64, T> : std::common_type<int64_t, T> { };
    
    template<class T>
    struct common_type<T, test::Int64> : std::common_type<T, int64_t> {};
    
    template<>
    struct common_type<test::Int64, test::Int64> : std::common_type<test::Int64> {};
}


namespace test
{
    
    using Nanoseconds = std::chrono::duration<Int64, std::nano>;
    using Microseconds = std::chrono::duration<Int64, std::micro>;
    using Milliseconds = std::chrono::duration<Int64, std::milli>;
    
    void test_adl(Nanoseconds) { std::cout << "ADL lookup succeeded." << std::endl; }
    
}
    

    
int main()
{
    using namespace test;
    
    Nanoseconds ns;
    test_adl(ns);
    
    Microseconds us;
    test_adl(us);
    
    std::chrono::duration_cast<std::chrono::nanoseconds>(ns);
    std::chrono::duration_cast<std::chrono::microseconds>(ns);
    std::chrono::duration_cast<std::chrono::milliseconds>(ns);
    std::chrono::duration_cast<std::chrono::seconds>(ns);
    
    std::chrono::duration_cast<std::chrono::nanoseconds>(us);
    std::chrono::duration_cast<std::chrono::microseconds>(us);
    std::chrono::duration_cast<std::chrono::milliseconds>(us);
    std::chrono::duration_cast<std::chrono::seconds>(us);
    
    std::chrono::nanoseconds() = Nanoseconds();
    std::chrono::nanoseconds() = Microseconds();
    std::chrono::nanoseconds() = Milliseconds();
    
    Nanoseconds() = std::chrono::nanoseconds();
    Nanoseconds() = std::chrono::microseconds();
    Nanoseconds() = std::chrono::milliseconds();
}

