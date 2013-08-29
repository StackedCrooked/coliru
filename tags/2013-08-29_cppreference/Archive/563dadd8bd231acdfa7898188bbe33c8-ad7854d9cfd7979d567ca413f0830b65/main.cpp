#include <limits>
#include <iostream>
#include <stdint.h>
#include <cstdlib>

using std::numeric_limits;

template <typename T, typename U>
    bool CanTypeFitValue(const U value) {
        if (numeric_limits<T>::is_signed == numeric_limits<U>::is_signed) {
            if (numeric_limits<T>::digits >= numeric_limits<U>::digits)
                return true;
            else
                return (static_cast<U>(numeric_limits<T>::min() ) <= value && static_cast<U>(numeric_limits<T>::max() ) >= value);
        }
        else {
            if (numeric_limits<T>::is_signed) {
                if (numeric_limits<T>::digits > numeric_limits<U>::digits) //Not >= in this case!
                    return true;
                else
                    return (static_cast<U>(numeric_limits<T>::max() ) >= value);
            }
            else ///U is signed, T is not
                if (value < static_cast<U> (0) )
                    return false;
                else
                    if (numeric_limits<T>::digits >= numeric_limits<U>::digits)
                        return true;
                    else
                        return (static_cast<U>(numeric_limits<T>::max() ) >= value);
        }
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

