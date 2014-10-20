#ifndef TOSTRING_H
#define TOSTRING_H

// Copyright Doug Gale
// MIT license, do as you please, don't blame me for anything, etc.

#include <sstream>
#include <iostream>

static inline void ToStringImpl(std::stringstream &)
{
}

template<typename T1>
void ToStringImpl(std::stringstream &ss, T1&& arg)
{
    ss << std::forward<T1>(arg);
}

template<typename T1, typename ...T>
void ToStringImpl(std::stringstream &ss, T1&& arg, T&& ...args)
{
    ss << std::forward<T1>(arg);
    ToStringImpl(ss, std::forward<T>(args)...);
}

template<typename ...T>
std::string ToString(T&& ...args)
{
    std::stringstream ss;
    ToStringImpl(ss, std::forward<T>(args)...);
    return ss.str();
}

template<typename ...T>
std::string ToString()
{
    return std::string();
}

#endif // TOSTRING_H


// test case
int main()
{
    std::cout << ToString("You can give numbers ", 123, " and even floating point ",123.45f, ", etc");
}
