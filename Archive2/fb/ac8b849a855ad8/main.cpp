#include <cstdint>
#include <iostream>

class Value {
public:
    Value(int16_t, int16_t*)         { std::cout << __PRETTY_FUNCTION__; } 
	Value(int32_t, int32_t*)         { std::cout << __PRETTY_FUNCTION__; } 
	Value(int64_t, int64_t*)         { std::cout << __PRETTY_FUNCTION__; } 
	Value(float, float*)             { std::cout << __PRETTY_FUNCTION__; } 
	Value(double, double*)           { std::cout << __PRETTY_FUNCTION__; } 
	Value(long double, long double*) { std::cout << __PRETTY_FUNCTION__; } 

    template <typename T> Value(T v)
        : Value(v, static_cast<T*>(nullptr)) 
    { std::cout << " from " << __PRETTY_FUNCTION__ << "\n"; }
};

int main()
{
    Value { 0 };
    Value { 0l };
    Value { 0.f };
    Value { 0. };
    Value { 0.l };
}
