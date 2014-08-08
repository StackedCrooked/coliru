#include <iostream>
#include <string>
#include <vector>
#include <chrono>


std::vector<uint8_t> data = []{
    std::vector<uint8_t> result;
    result.reserve(100000);
    while (result.size() != result.capacity())
    {
        result.push_back(result.size());
    }
    return result;
}();


// pass by value
uint32_t by_val(uint8_t* b, uint8_t* e, uint32_t sum);

// pass by reference
void by_ref(uint8_t* b, uint8_t* e, uint32_t& sum);

// NOTE: Implementation is here: http://coliru.stacked-crooked.com/a/bf62399c690ea7c4


int main()
{
    using namespace std::chrono;
    typedef high_resolution_clock Clock;
    
    auto test_by_ref = [&]
    {
        auto start_time = Clock::now();
        uint32_t sum = 0;
        by_ref(data.data(), data.data() + data.size(), sum);
        auto elapsed = Clock::now() - start_time;
        std::cout << "by_ref: " << duration_cast<microseconds>(elapsed).count() << "us (sum=" << sum << ")" << std::endl;
    };
    
    auto test_by_val = [&]
    {
        auto start_time = Clock::now();
        uint32_t sum = 0;
        sum = by_val(data.data(), data.data() + data.size(), sum);
        auto elapsed = Clock::now() - start_time;
        std::cout << "by_val: " << duration_cast<microseconds>(elapsed).count() << "us (sum=" << sum << ")" << std::endl;
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