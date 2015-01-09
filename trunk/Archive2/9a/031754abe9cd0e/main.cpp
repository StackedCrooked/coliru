#include <iostream>
#include <vector>

template <typename T>
using identity = T;

struct Converter
{
    template <typename ConvT,
              template <typename...> class ConT = identity,
              typename FromT>
    static ConT<ConvT> convert(FromT type);
};

template <typename ConvT,
          template <typename...> class ConT,
          typename FromT>
ConT<ConvT> Converter::convert(FromT type)
{
    return ConT<ConvT>{ static_cast<ConvT>(type) };
}

int main()
{
    std::vector<double> v = Converter::convert<double, std::vector>(42);
    std::cout << v[0] << std::endl;
    
    double d = Converter::convert<double>(42);
    std::cout << d << std::endl;
}
