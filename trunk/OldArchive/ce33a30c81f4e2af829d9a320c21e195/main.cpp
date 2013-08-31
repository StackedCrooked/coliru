#include <chrono>

std::chrono::milliseconds operator "" _ms(unsigned long long v)
{return std::chrono::milliseconds(v);}

int main() {
   auto v = 3_ms;
}