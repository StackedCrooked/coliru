#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <boost/type_traits.hpp>
#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/include/push_back.hpp>
#include <boost/tuple/tuple.hpp>

namespace Test {
    typedef enum {
        NONE = 0x00000000,
        VAL1 = 0x00000001,
        VAL2 = 0x00000002,
        ALL = 0xFFFFFFFF
    } Type;
}

int main()
{
    /*boost::fusion::vector<std::string, std::string, bool> parameters_;
    
    boost::fusion::push_back(parameters_, boost::make_tuple("abc","value", true));
    
    std::cout<< "hm "<< boost::fusion::value_at<0>(parameters_) << " " <<boost::fusion::value_at<1>(parameters_) << (boost::fusion::value_at<2>(parameters_)?"[default]":"")<<std::endl;*/
    
    std::cout << boost::is_fundamental<std::string>::value << std::endl;
    /*uint32_t val = 0, cnt = 0;
    while(val < (Test::ALL)) {
        std::cout << "i(2^"<< cnt<<") = " << val<< std::endl;
        cnt++;
        val = (1<<cnt);
    }*/
}
