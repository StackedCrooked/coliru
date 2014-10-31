#include <iostream>
#include <type_traits>

struct CByteArray {};
struct Variant {};

template <typename T>
CByteArray serializePodType(const T& value);

template <typename T>
typename std::enable_if<std::is_pod<T>::value, CByteArray>::type
serialize(const T& value)
{
    return serializePodType(value);
}

template <typename T>
typename std::enable_if<std::is_convertible<T, Variant>::value, CByteArray>::type
serialize(const T& value)
{
    return serialize(Variant(value));
}

template <typename T>
T serialize(const T& value)
{
    std::cerr << "Unsupported type\n";
    return CByteArray();
}
