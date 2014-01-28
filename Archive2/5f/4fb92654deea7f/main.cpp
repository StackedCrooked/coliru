#include <iostream>
#include <limits>
#include <stdexcept>
#include <type_traits>

template<typename DestType, typename SrcType>
DestType range_check_and_convert(SrcType const& src)
{
    static_assert(sizeof(SrcType) > sizeof(DestType), 
        "SrcType must be larger than DestType");
    static_assert(std::is_integral<SrcType>::value &&
                  std::is_integral<DestType>::value, "integral types only");
        
    if(src > static_cast<SrcType>(std::numeric_limits<DestType>::max())) {
        throw std::out_of_range("input too big");
    } else if(src < static_cast<SrcType>(std::numeric_limits<DestType>::min())) {
        throw std::out_of_range("input too small");
    }
    
    return static_cast<DestType>(src);
}

int main()
{
    std::cout << range_check_and_convert<unsigned short>(65535) << std::endl;
    std::cout << range_check_and_convert<short>(32767L) << std::endl;
    std::cout << range_check_and_convert<short>(-32768L) << std::endl;
//    std::cout << range_check_and_convert<unsigned short>(65536) << std::endl; // throws
//    std::cout << range_check_and_convert<unsigned short>(-1L) << std::endl; // throws
//    std::cout << range_check_and_convert<long>(1) << std::endl; // static_assert fails
}
