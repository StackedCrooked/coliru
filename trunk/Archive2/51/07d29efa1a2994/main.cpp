#include <string>
#include <functional>
#include <iostream>
#include <utility>
#include <type_traits>

/* Variant container */
struct blackbox
{
    int int_value() const { return 42; }
    bool bool_value() const { return true; }
    std::string string_value() const { return "str"; }
};

/* Unpack function templates */
template<typename T>
T unpack(const blackbox &v)
{
    static_assert(sizeof(T) == 0, "This template has to be specialized");
}

template<>
int unpack(const blackbox &v)
{
    return v.int_value();
}

template<>
bool unpack(const blackbox &v)
{
    return v.bool_value();
}

template<>
std::string unpack(const blackbox &v)
{
    return v.string_value();
}

/* Call function with arguments extracted from blackbox */
template<typename T>
void call(std::function<void(T)> f, const blackbox &v)
{
    f(unpack<typename std::decay<T>::type>(v));
}

/* Sample functions */

void f_int(int i) { std::cout << "f_int(" << i << ")" << std::endl; }
void f_bool(bool b) { std::cout << "f_bool(" << b << ")" << std::endl; }
void f_str(std::string s) { std::cout << "f_str(" << s << ")" << std::endl; }
void f_str_ref(const std::string &s) { std::cout << "f_str_ref(" << s << ")" << std::endl; }

int main()
{
    blackbox b;

    // direct call
    f_str_ref(b.string_value());

    // indirect call
    call(std::function<void(int)>(f_int), b);
    call(std::function<void(bool)>(f_bool), b);
    call(std::function<void(std::string)>(f_str), b);
    call(std::function<void(const std::string&)>(f_str_ref), b); // works

    return 0;
}