#include <iostream>
#include <vector>

struct Converter
{
    template <typename ConvT,
              typename FromT>
    static ConvT convert(FromT type);
    
    template <typename ConvT,
              template <typename...> class ConT,
              typename FromT>
    static ConT<ConvT> convert(FromT type);
};

template <typename ConvT,
          typename FromT>
ConvT Converter::convert(FromT type)
{
    return static_cast<ConvT>(type);
}

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
