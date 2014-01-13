#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/type_traits/is_unsigned.hpp>

template <bool is_unsigned>
struct unsigned_checker
{
    template<typename String_type>
    static inline void do_check(const String_type & str) { }
};

template <>
struct unsigned_checker<true>
{
    template<typename String_type>
    static inline void do_check(const String_type & str)
    {
        if( str[0] == '-' ) boost::throw_exception( boost::bad_lexical_cast() );
    }
};

template<typename Target, typename Source>
inline Target forced_lexical_cast(const Source &arg)
{
    unsigned_checker< boost::is_unsigned<Target>::value >::do_check(arg);
    return boost::lexical_cast<Target>( arg );
}

int main()
{
    std::istringstream iss("-89");
    std::string s;
    iss >> s;
    try { std::cout << forced_lexical_cast<unsigned int>(s); }
    catch (boost::bad_lexical_cast const&) { std::cout << "OK"; }
}
    