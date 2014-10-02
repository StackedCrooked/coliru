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
    
    /** test adl lookup */
    Nanoseconds ns;
    Microseconds us;
    test_adl(ns);    
    test_adl(us); // ADL + implicit conversion to Nanoseconds
    
    
    /** test interoperability with std::chrono duration types */
    using namespace std::chrono;
    
    duration_cast<nanoseconds>(Nanoseconds());
    duration_cast<nanoseconds>(Microseconds());
    
    duration_cast<seconds>(Nanoseconds());
    duration_cast<seconds>(Microseconds());
    
    nanoseconds() = Nanoseconds();
    nanoseconds() = Milliseconds();
    
    Nanoseconds() = nanoseconds();
    Nanoseconds() = milliseconds();
}

