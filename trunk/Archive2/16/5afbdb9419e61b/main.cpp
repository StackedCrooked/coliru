#include <iostream>
#include <string>
#include <vector>

#include <boost/variant.hpp>

typedef boost::variant<int, double> Type;

struct functor {
    void operator(int i, double d) const {
        // nothing   
    }
};

template<typename From, typename To>
struct Convert;

template<typename From>
struct Convert<From, int> {
    int operator ()(From f) {
        return boost::get<int>(f);   
    }
};

template<typename From>
struct Convert<From, float> {
    int operator ()(From f) {
        return boost::get<int>(f);   
    }
};




int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
