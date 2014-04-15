#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <iostream>

namespace mp = boost::multiprecision;

template <typename T>
std::string to_pretty_string(T const& v)
{
    std::string s = v.str(0, std::ios_base::scientific);
    assert(s.length()>3); // min: 0.e
    switch (s[0])
    { // normalized scientific always has #.####### form of mantissa
        case '-':
        case '+': assert(s[2] == '.'); break;
        default:  assert(s[1] == '.'); break;
    }

    auto exp = s.find('e');
    if (std::string::npos != exp && exp > 0)
    {
        for(size_t pos = exp-1; pos; --pos)
        {
            if (s[pos] != '0')
            {
                if (pos > 0 && s[pos]=='.') 
                {
                    --pos;
                }
                // remove run of 0's if applicable
                s.erase(pos+1, exp-pos-1); 
                break;
            }
        }
    }
    return std::move(s);
}

int main()
{
    typedef mp::number<mp::cpp_dec_float<100>> mp_type;
    mp_type test_num("7.000000000000000000000000000000000000000000000000000000000000e-01");

    std::cout << to_pretty_string(test_num) << '\n';
}

