#include <iostream>
#include <vector>

class Converter
{
public:
   Converter() {};

    template <typename ConvT, typename FromT>
    static ConvT convert(FromT type);
    
    template <typename ConvT, template <typename...> class ConT, typename FromT>
    static ConT<ConvT> convert(FromT type);
};

template <typename ConvT, typename FromT>
ConvT Converter::convert(FromT type)
{
    return static_cast<ConvT>(type);
}

template <> double Converter::convert<double,int>(int type)
{
    return 22.2;
}

template <typename ConvT, template <typename...> class ConT, typename FromT>
ConT<ConvT> Converter::convert(FromT type)
{
    return ConT<ConvT>{ static_cast<ConvT>(type) };
}

int main()
{
    std::vector<double> myDoubleVec = Converter::convert<double, std::vector>(42);
    std::cout << myDoubleVec[0];
}
