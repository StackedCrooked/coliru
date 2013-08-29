#include <limits>
#include <iostream>
#include <stdint.h>
#include <cstdlib>


using std::numeric_limits;

template <typename T, typename U>
    bool CanTypeFitValue(const U value) {
        const intmax_t bot_t = intmax_t(numeric_limits<T>::min() );
        const intmax_t bot_u = intmax_t(numeric_limits<U>::min() );
        const uintmax_t top_t = uintmax_t(numeric_limits<T>::max() );
        const uintmax_t top_u = uintmax_t(numeric_limits<U>::max() );
        return !( (bot_t > bot_u && value < static_cast<U> (bot_t)) || (top_t < top_u && value > static_cast<U> (top_t)) );        
    }

int main(int argc, char** argv) {
    std::cout << CanTypeFitValue<int>(numeric_limits<long>::max() ) << std::endl;
    std::cout << CanTypeFitValue<int>(numeric_limits<unsigned int>::max() ) << std::endl;
    std::cout << CanTypeFitValue<int>(static_cast<unsigned int> (500) ) << std::endl;
    std::cout << CanTypeFitValue<char>(static_cast<unsigned int> (200) ) << std::endl;
    std::cout << CanTypeFitValue<unsigned char>(static_cast<unsigned int> (200) ) << std::endl;
    std::cout << CanTypeFitValue<int>(numeric_limits<long>::max() ) << std::endl;
    std::cout << CanTypeFitValue<unsigned int>(static_cast<char> (-1) ) << std::endl;
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

