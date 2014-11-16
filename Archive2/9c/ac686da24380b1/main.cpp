#include <boost/variant.hpp>
#include <vector>
#include <iostream>

namespace detail {
    template <typename T>
    struct get_with_default_visitor : boost::static_visitor<T> {
        T default_;
        get_with_default_visitor(T dv) : default_(dv) {}

        T const& operator()(T const& v) const { return v; }

        template <typename Other> T operator()(Other const&) const {
            return default_;
        }
    };
}

template<typename T, typename Container> T Get(Container const& data, size_t i, T defaultvalue = T())
{
    if (i < data.size())
        return boost::apply_visitor(detail::get_with_default_visitor<T>(defaultvalue), data[i]);
    else
        return defaultvalue;
}

int main() {
    std::vector<boost::variant<int, float, std::string> > data { 
        42, 3.14f, std::string("hello world") };
    
    for (int i = 0; i < 5; ++i) std::cout << Get<int>(data, i, -99) << "\t";
    std::cout << "\n";
    
    for (int i = 0; i < 5; ++i) std::cout << Get<float>(data, i, -9999e99) << "\t";
    std::cout << "\n";
    
    for (int i = 0; i < 5; ++i) std::cout << "'" << Get<std::string>(data, i, "#error#") << "'\t";
    std::cout << "\n";
}
