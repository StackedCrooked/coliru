#include <chrono>
#include <iostream>

int main()
{
    using namespace std::chrono;
    auto one_second = seconds(1);
    auto half_a_second = one_second / 2;
    auto half_a_second_in_milliseconds = duration_cast<milliseconds>(half_a_second);    
    std::cout << half_a_second_in_milliseconds.count() << std::endl;
}
