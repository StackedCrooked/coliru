#include <type_traits>

struct CByteArray {};
struct HLVariant {
    HLVariant() {}
    HLVariant(const HLVariant&) {}
    HLVariant(const CByteArray&) {}

    };

static CByteArray serialize(const HLVariant& /* value */)
{
    return CByteArray();
}

template <typename T>
static typename std::enable_if<std::is_pod<T>::value, CByteArray>::type
serialize(const T& /* value*/)
{
    static_assert(std::is_pod<T>::value, "Not a POD type");
    return CByteArray();
}

template <typename T>
static typename std::enable_if<!std::is_pod<T>::value, CByteArray>::type
serialize(const T& value)
{
    return serialize(HLVariant(value));
}

int main()
{
    int i = 0;
    serialize(i);
    serialize(CByteArray());
    serialize(HLVariant());
}
