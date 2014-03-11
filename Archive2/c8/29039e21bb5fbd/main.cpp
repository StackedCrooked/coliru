#include <iostream>

template<typename... Args> class X;

template<typename T>
class X<T> {
 public:
    T value;
    X(T value_) : value(value_) {}
};

template<typename T, typename... Args>
class X<T, Args...> : public X<Args...> {
 public:
    T value;
    X(T value_, Args... args) : X<Args...>(args...), value(value_) {}
};

template<typename T>
std::ostream& operator <<(std::ostream& stream, const X<T>& value_) {
    stream << value_.value;
    return stream;
}

template<typename T, typename... Args>
std::ostream& operator <<(std::ostream& stream, const X<T, Args...>& value_) {
    stream << value_.value << " " << static_cast<X<Args...> >(value_);
    return stream;
}

class Person : public X<std::string, int>{
 public:
    Person(std::string name, int age) : X<std::string, int>(name, age) {}
};


int main()
{
   std::cout << Person("Me", 35) << std::endl;
   return 0;
}