#include <iostream>
#include <vector>

template <typename T> using identity = T;

class Converter
{
public:
    Converter() {};

    template <typename ConvT, template <typename...> class ConT = identity, typename FromT>
    static ConT<ConvT> convert(FromT type);
};

template <typename ConvT, template <typename...> class ConT, typename FromT>
ConT<ConvT> Converter::convert(FromT type)
{
    return ConT<ConvT>{ static_cast<ConvT>(type) };
}

template <> double Converter::convert<double, identity, int>(int type)
{
    return 22.2;
}

int main()
{
    std::vector<double> myDoubleVec = Converter::convert<double, std::vector>(42);
    std::cout << myDoubleVec[0];
}
