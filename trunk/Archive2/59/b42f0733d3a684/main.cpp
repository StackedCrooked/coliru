#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <memory>

struct Converter
{
    template <typename ConvT,
              typename FromT>
    static ConvT convert(FromT type);
    
    template <typename ConvT,
              template <typename T, typename A = std::allocator<T> > class ConT,
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
          template <typename T, typename A = std::allocator<T> > class ConT,
          typename FromT>
ConT<ConvT> Converter::convert(FromT type)
{
    return ConT<ConvT>(1, static_cast<ConvT>(type));
}

int main()
{
    std::vector<double> v = Converter::convert<double, std::vector>(42);
    std::cout << v[0] << std::endl;
    
    std::list<double> l = Converter::convert<double, std::list>(42);
    std::cout << l.front() << std::endl;
    
    std::deque<double> d = Converter::convert<double, std::deque>(42);
    std::cout << d[0] << std::endl;
}
