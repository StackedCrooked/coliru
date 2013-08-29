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
    std::cout << 0.5 << ' ' << int(0.5) << ' ' << CanTypeFitValue<int>(0.5) << std::endl;
}