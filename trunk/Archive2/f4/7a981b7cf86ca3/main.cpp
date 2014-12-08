#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace V1{
class Test{
public:
    typedef enum{
        mc_ePercentageMax,
        mc_ePercentageMin,
        mc_eDrift,
        mc_nCount
    } eSVSCalculation;
};
}
        
namespace V2{
class Test{
public: 
    typedef V1::Test::eSVSCalculation mt_eEnum;
};
}

typedef std::map<V1::Test::eSVSCalculation,double> map_1;
typedef std::map<V2::Test::mt_eEnum       ,double> map_2;

void f (map_1 m)
{
    for (const auto& i : m){
        std::cout<<i.first<<" "<<i.second;
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << "    ";
    }
    return os;
}

int main()
{
    map_2 m;
    m[V2::Test::mt_eEnum::mc_eDrift] = 1.0;
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
    f(m);
}
