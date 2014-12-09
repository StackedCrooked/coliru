#include <sstream>
#include <iostream>

#include <boost/variant.hpp>

using namespace boost;

using blob_t = std::vector<uint8_t>;
using field_value_t = boost::variant<double, char const*, long, blob_t/*, boost::date_time, std::vector<uint8_t>*/>;

struct handler : static_visitor<std::string> {

    std::string operator()(double)      const { return "It's a double"; }
    std::string operator()(char const*) const { return "It's a C string (ew!)"; }
    std::string operator()(long)        const { return "It's a long"; }
    std::string operator()(blob_t)      const { return "It's a long"; }
    
    template<typename T>
    std::string operator()(T const&)    const { throw "Not implemented"; } // TODO proper exception
};

void handle_field(field_value_t const& value) {
    std::cout << apply_visitor(handler(), value) << "\n";
}

int main() {

    handle_field(blob_t { 1,2,3 });
    handle_field("Hello world");
    handle_field(3.14);

}
