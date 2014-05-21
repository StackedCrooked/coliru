#include <iostream>
#include <type_traits>

template <int n>
class failclass;

template<int n1, typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<< (std::basic_ostream<_CharT, _Traits>& _os,
            const failclass<n1>& _x);
            
template <int n>
class failclass
{
private:
    static constexpr int k = n;

public:
    template<int n1, typename _CharT, typename _Traits>
    friend std::basic_ostream<_CharT, _Traits>&
    operator<< (std::basic_ostream<_CharT, _Traits>& _os,
                const failclass<n1>& _x);
};

template<int n1, typename _CharT, typename _Traits>
std::basic_ostream<_CharT, _Traits>&
operator<< (std::basic_ostream<_CharT, _Traits>& _os,
            const failclass<n1>& _x)
{
    _os << _x.k;
    return _os;
}

int main() {
       failclass<1> f;
       std::cout << f;
}