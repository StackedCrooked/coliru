#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class C
{
public:
    typedef std::vector<std::string> Info;
    
    explicit C(Info const& info)
        : info_(info)
    {}
    std::string text(Info::size_type i) const
    {
        return info_[i];
    }
private:
    Info info_;
};

int get_max_width(std::vector<C> const& c_vec, C::Info::size_type info_n)
{
    std::vector<C>::const_iterator max = std::max_element(c_vec.cbegin(), c_vec.cend(),
        [info_n](C const& lhs, C const& rhs)
        { return lhs.text(info_n).length() < rhs.text(info_n).length(); });
        
    return max != c_vec.end() ? max->text(info_n).length() : 0;
}

#include <functional>
#include <boost/phoenix.hpp>

int get_max_width_phx(std::vector<C> const& c_vec, C::Info::size_type info_n)
{
    namespace phx = boost::phoenix;
    using namespace phx::arg_names;

    std::vector<C>::const_iterator max = std::max_element(c_vec.begin(), c_vec.end(),
        phx::bind(std::mem_fun_ref(&std::string::length), phx::bind(&C::text, arg1, phx::val(info_n))) < 
        phx::bind(std::mem_fun_ref(&std::string::length), phx::bind(&C::text, arg2, phx::val(info_n)))
      );
        
    return max != c_vec.end() ? max->text(info_n).length() : 0;
}

int main()
{
    std::vector<C> c_vec{C{{"Info00", "Info01..."}}, C{{"Info10..", "Info11"}}};
    
    std::cout << get_max_width(c_vec, 0) << '\n';
    std::cout << get_max_width(c_vec, 1) << '\n';
    
    std::cout << get_max_width_phx(c_vec, 0) << '\n';
    std::cout << get_max_width_phx(c_vec, 1) << '\n';
}
