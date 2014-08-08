#include <iostream>
#include <string>
#include <vector>
#include <chrono>


typedef uint32_t sum_t;
typedef uint8_t byte_t;


std::vector<byte_t> data = []{
    std::vector<byte_t> result;
    result.reserve(100000);
    while (result.size() != result.capacity())
    {
        result.push_back(result.size());
    }
    return result;
}();


// pass by value
sum_t by_val(byte_t* b, byte_t* e, sum_t sum);

// pass by reference
void by_ref(byte_t* b, byte_t* e, sum_t& sum);



int main()
{
    using namespace std::chrono;
    typedef high_resolution_clock Clock;
    
    auto test_by_ref = [&]
    {
        auto start_time = Clock::now();
        sum_t sum = 0;
        by_ref(data.data(), data.data() + data.size(), sum);
        auto elapsed = Clock::now() - start_time;
        std::cout << "by_ref: " << duration_cast<microseconds>(elapsed).count() << "us (sum=" << int(sum) << ")" << std::endl;
    };
    
    auto test_by_val = [&]
    {
        auto start_time = Clock::now();
        sum_t sum = 0;
        sum = by_val(data.data(), data.data() + data.size(), sum);
        auto elapsed = Clock::now() - start_time;
        std::cout << "by_val: " << duration_cast<microseconds>(elapsed).count() << "us (sum=" << int(sum) << ")" << std::endl;
    };
    
    // Test by_ref
    test_by_ref();
    test_by_ref();
    test_by_ref();
    
    // Test by_val
    test_by_val();
    test_by_val();
    test_by_val();
}