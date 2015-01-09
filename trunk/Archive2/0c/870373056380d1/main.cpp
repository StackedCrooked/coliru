#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <memory>

class Converter
{
public:
   Converter() {};

    template <typename ConvT, typename FromT>
    static ConvT convert(FromT type);
    
    template <typename ConvT, template <typename T, typename A = std::allocator<T> > class ConT, typename FromT>
    static ConT<ConvT> convert(FromT type);
};

template <typename ConvT, typename FromT>
ConvT Converter::convert(FromT type)
{
    return static_cast<ConvT>(type);
}

template <>
double Converter::convert<double,int>(int type)
{
    return 22.2;
}

template <typename ConvT, template <typename T, typename A = std::allocator<T> > class ConT, typename FromT>
ConT<ConvT> Converter::convert(FromT type)
{
    return ConT<ConvT>(1, static_cast<ConvT>(type));
}

int main()
{
    std::vector<double> myDoubleVec = Converter::convert<double, std::vector>(42);
    std::cout << myDoubleVec[0] << std::endl;
    
    std::list<double> myDoubleList = Converter::convert<double, std::list>(42);
    std::cout << myDoubleList.front() << std::endl;
    
    std::deque<double> myDoubleDeque = Converter::convert<double, std::deque>(42);
    std::cout << myDoubleDeque[0] << std::endl;
}
