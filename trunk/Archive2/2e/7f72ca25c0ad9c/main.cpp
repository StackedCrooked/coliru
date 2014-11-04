
#include <type_traits>

struct CByteArray {};

struct CIODevice {
template <typename T>
    CIODevice& operator<< (T)
    {
        static_assert(std::is_pod<T>::value, "This method is only intended for POD types");
        return *this;
    }

    template <typename T>
    CIODevice& operator>> (T&)
    {
        static_assert(std::is_pod<T>::value, "This method is only intended for POD types");
        return *this;
    }
};

template <>
CIODevice& CIODevice::operator<< (CByteArray)
{
    return *this;
}

int main()
{
    CIODevice device;
    int i = 0;
    device << i;
    device >> i;
    return 0;
}