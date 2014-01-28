#include <iostream>
#include <string>
#include <vector>

struct Group {virtual ~Group();};

namespace Groups {

struct Null : Group {};

struct Cyclic : Group {};

template <typename F> struct Product : Group
    {typedef typename F::domain_type index_type;
     Product (const F & src) : _factor (src) {}
     template <typename F1> Product (const F1 & src);
     const Group & factor (const index_type & i)
        {return _factor (i);}
    private:
     const F _factor;};

template <typename F> struct CoProduct : Group
    {typedef typename F::domain_type index_type;
     CoProduct (const F & src) : _factor (src) {}
     template <typename F1> CoProduct (const F1 & src);
     const Group & factor (const index_type & i)
        {return _factor (i);}
    private:
     const F _factor;};

}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl;
}
