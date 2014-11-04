#include <type_traits>

struct CByteArray {};
struct HLVariant {
    HLVariant() {}
    HLVariant(const HLVariant&) {}
    HLVariant(const CByteArray&) {}

    };

inline CByteArray serialize(const HLVariant& /* value */)
{
    return CByteArray();
}

template <typename T>
inline CByteArray serialize(std::true_type, const T& /* value*/)
{
    static_assert(std::is_pod<T>::value, "Not a POD type");
    return CByteArray();
}

template <typename T>
inline CByteArray serialize(std::false_type, const T& value)
{
    return serialize(HLVariant(value));
}

template <typename T>
inline CByteArray serialize(const T& value)
{
    return serialize(std::is_pod<T>{}, value);
}

int main()
{
    int i = 0;
    serialize(i);
    serialize(CByteArray());
    serialize(HLVariant());
}
