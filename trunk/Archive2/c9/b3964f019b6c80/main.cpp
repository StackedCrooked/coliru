#include <iostream>

struct NormalType { };

struct SpecialType { typedef int special; };

template <typename U>
class has_special
{
private:
    typedef char false_type;
    struct true_type { char x[2]; };
    
    template<typename T>
    static true_type check(typename T::special*);
    template<typename T> static false_type check(...);
public:
    static bool const value = sizeof(check<U>(0)) == sizeof(true_type);
};

template <typename T, bool IsSpecial = has_special<T>::value>
struct DetectSpecial {
    void detected() { std::cout << "Not special...\n"; }
};

template <typename T>
struct DetectSpecial<T, true> {
    void detected() { std::cout << "Special!\n"; }
};

int main()
{
    DetectSpecial<NormalType>().detected();
    DetectSpecial<SpecialType>().detected();
}
