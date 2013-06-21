#include <iostream>

template <typename T, typename U>
constexpr bool CanTypeFitValue(const U value)
{return ((value>0)==(T(value)>0)) && U(T(value))==value;}

int main(int argc, char** argv) {
    for (int i = 1; i < argc; i++) {
        const int value = atoi(argv[i]);
        std::cout << value << ": ";
        std::cout << CanTypeFitValue<int8_t>(value) << " ";
        std::cout << CanTypeFitValue<uint8_t>(value) << " ";
        std::cout << CanTypeFitValue<int16_t>(value) << " ";
        std::cout << CanTypeFitValue<uint16_t>(value) << " ";
        std::cout << CanTypeFitValue<int32_t>(value) << " ";
        std::cout << CanTypeFitValue<uint32_t>(value) << " ";
        std::cout << CanTypeFitValue<int64_t>(value) << " ";
        std::cout << CanTypeFitValue<uint64_t>(value) << std::endl;
        }

}