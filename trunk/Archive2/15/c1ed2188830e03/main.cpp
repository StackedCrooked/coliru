#include <iostream>
#include <iomanip>
#include <sstream>
#include <limits>
#include <typeinfo>
#include <boost/lexical_cast.hpp>

template <typename T>
inline T fast_lexical_cast(const float& arg)
{
    std::stringstream ss;
	ss << std::setprecision(std::numeric_limits<float>::digits10) << arg;
	if (!ss)
		boost::throw_exception(boost::bad_lexical_cast(typeid(std::string), typeid(float)));
	
	return ss.str();
}

inline std::string pretty_lexical_cast(const float& arg)
{
    const int asInt = static_cast<int>(1/arg);
    if (fabs(arg) > 0 && fabs(arg) < 1 && (1/arg == asInt)) {
		return (asInt < 0 ? "-1/" : "1/") + fast_lexical_cast<std::string>(abs(asInt));
	}
	else {
		return fast_lexical_cast<std::string>(arg);
	}
}

int main()
{
    std::cout << pretty_lexical_cast(-2.0) << std::endl;
    std::cout << pretty_lexical_cast(-1.5) << std::endl;
    std::cout << pretty_lexical_cast(-0.5) << std::endl;
    std::cout << pretty_lexical_cast(0) << std::endl;
    std::cout << pretty_lexical_cast(0.5) << std::endl;
    std::cout << pretty_lexical_cast(1.5) << std::endl;
    std::cout << pretty_lexical_cast(2.0) << std::endl;
}