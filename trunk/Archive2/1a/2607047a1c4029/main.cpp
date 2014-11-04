#include <type_traits>

struct CByteArray {};
struct HLVariant {
    HLVariant() {}
    HLVariant(const HLVariant&) {}
    HLVariant(const CByteArray&) {}

    };

template <typename> struct Serializer;

template <>
struct Serializer<HLVariant>
{
    static CByteArray serialize(const HLVariant& value)
    {
        return CByteArray();
    }
};

template <typename T>
struct Serializer
{
    template <typename U = T>
    static typename std::enable_if<std::is_pod<U>::value, CByteArray>::type serialize(const U&)
    {
        static_assert(std::is_pod<U>::value, "Not a POD type");
        return CByteArray();
    }

    template <typename U = T>
    static typename std::enable_if<!std::is_pod<U>::value, CByteArray>::type serialize(const U&)
    {
        return Serializer<HLVariant>::serialize(HLVariant(value));
    }
};

int main()
{
    int i = 0;
    Serializer<int>::serialize(i);
    Serializer<CByteArray>::serialize(CByteArray());
    Serializer<HLVariant>::serialize(HLVariant());
}