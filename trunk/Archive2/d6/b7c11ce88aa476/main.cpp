// Remove the small inefficiencies, i.e., guarantee no allocations on Fizz, Buzz, or FizzBuzz, changing as least as possible.
//
// What you can change:
// - what gets returned in the if bodies
// - the return type of the fizz_buzz function
// - #includes
// - if you really want, you can define a class before the fizz_buzz function
//
// What you cannot change:
// - return enumerators or other non-stringy stuff instead of the strings for "Fizz", "Buzz", and "FizzBuzz"
//
// The goal is to return both static and dynamic strings without redundant allocations/copies, so try not to change things in a way that goes against that spirit.

#include <string>
#include <iostream>
#include <limits>
#include <algorithm>

struct maybe_static_maybe_dynamic {
    const char* str;
    bool is_static;
    maybe_static_maybe_dynamic(const char* str, bool b = true): str(str), is_static(b) {}
    ~maybe_static_maybe_dynamic() {
        if(!is_static) {
            delete str;
        }
    }
    
    friend std::ostream& operator<<(std::ostream& out, const maybe_static_maybe_dynamic& str) {
        return out << str.str;
    }
};

template<typename T>
maybe_static_maybe_dynamic to_string(T t) {
    char* arr  = new char[std::numeric_limits<T>::digits10 + 1];
    const T zero = { 0 };
    size_t pos = 0;

    T copy = t;
    do {
        arr[pos] = '0' + std::abs(copy % 10);
        ++pos;
        copy /= 10;
    }
    while(copy != zero);

    if(t < zero) {
        arr[pos] = '-';
        ++pos;
    }

    arr[pos] = '\0';

    std::reverse(arr, arr + pos);
    return { arr, false };
}

maybe_static_maybe_dynamic fizz_buzz(int i) {
    if(i % 15 == 0) {
        return { "FizzBuzz" };          // slight inefficiency here: allocating a string and copying this static string into it
    } else if(i % 5 == 0) {
        return { "Buzz" };              // same here
    } else if(i % 3 == 0) {
        return { "Fizz" };              // and here
    } else {
        return ::to_string(i);   // this allocation will have to stay, I guess
    }
}

int main() {
    for(int i = 1; i <= 100; ++i) std::cout << fizz_buzz(i) << '\n';
}