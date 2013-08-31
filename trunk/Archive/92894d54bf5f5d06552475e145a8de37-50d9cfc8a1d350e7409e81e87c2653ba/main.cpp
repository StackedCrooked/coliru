#include <cstdint>
#include <iosfwd>
#include <limits>
#include <type_traits>

template <typename T>
class print_binary_helper;

template <typename T>
std::ostream& operator<<(std::ostream& sink,
                         const print_binary_helper<T> source);
                         
template <typename T>
std::wostream& operator<<(std::wostream& sink,
                          const print_binary_helper<T> source);
                          
template <typename T>
print_binary_helper<T> print_binary(T value);



template <typename T>
class print_binary_helper
{
public:
    static_assert(std::is_integral<T>::value,
                  "Cannot print non-integer in binary.");

    friend print_binary_helper<T> print_binary<>(const T value);

    friend std::ostream& operator<< <>(std::ostream& sink,
                                    const print_binary_helper<T> source);

    friend std::wostream& operator<< <>(std::wostream& sink,
                                     const print_binary_helper<T> source);

private:
    explicit print_binary_helper(T value) :
    mValue(value)
    {}

    template <typename Sink, typename Char>
    Sink& do_print(Sink& sink, Char on, Char off) const
    {
        for (auto mask = T(1) << (std::numeric_limits<T>::digits - 1);
             mask != 0; mask >>= 1)
        {
            const auto isOn = (mValue & mask) != 0;
            sink << (isOn ? on : off);
        }

        return sink;
    }

    T mValue;
};

template <typename T>
std::ostream& operator<<(std::ostream& sink,
                         const print_binary_helper<T> source)
{
    return source.do_print(sink, '1', '0');
}

template <typename T>
std::wostream& operator<<(std::wostream& sink,
                          const print_binary_helper<T> source)
{
    return source.do_print(sink, L'1', L'0');
}

template <typename T>
print_binary_helper<T> print_binary(T value)
{
    return print_binary_helper<T>(value);
}



#include <iostream>

int main()
{
    std::cout << print_binary(0) << std::endl;
    std::cout << print_binary(111605) << std::endl;
    std::cout << print_binary(static_cast<unsigned long long>(-1) - 1) << std::endl;
}
