#include <boost/variant.hpp>
#include <string>
#include <stdexcept>
#include <iostream>

class WeirdVariant {
    using variant = boost::variant<int, std::string>;
    variant data;
    
    struct invalid_conversion_helper : boost::static_visitor<WeirdVariant> {
        template<typename P>
        WeirdVariant operator()(P&&) const {
            throw std::runtime_error{"invalid conversion"};
        }

        template<typename P1, typename P2>
        WeirdVariant operator()(P1&&, P2&&) const {
            throw std::runtime_error{"invalid conversion"};
        }
    };
    
    struct print_visitor : boost::static_visitor<void> {
        std::ostream& os;
        
        print_visitor(std::ostream& os) : os(os) {}
        
        template<typename T>
        void operator()(T const& t) const {
            os << t;
        }
    };
    
public:
    WeirdVariant(int i) : data(i) {}
    WeirdVariant(std::string s) : data(std::move(s)) {}
    
    friend WeirdVariant operator+(WeirdVariant const& lhs, WeirdVariant const& rhs) {
        struct add_visitor : invalid_conversion_helper {
            using invalid_conversion_helper::operator();

            WeirdVariant operator()(int x, int y) const {
                return x + y;
            }
            
            WeirdVariant operator()(int x, std::string const& y) const {
                return std::to_string(x) + y;
            }
            
            WeirdVariant operator()(std::string const& x, int y) const {
                return x + std::to_string(y);
            }
            
            WeirdVariant operator()(std::string const& x, std::string const& y) const {
                return x + y;
            }
        };
        return boost::apply_visitor(add_visitor{}, lhs.data, rhs.data);
    }
    
    friend WeirdVariant operator-(WeirdVariant const& lhs, WeirdVariant const& rhs) {
        struct sub_visitor : invalid_conversion_helper {
            using invalid_conversion_helper::operator();

            WeirdVariant operator()(int x, int y) const {
                return x - y;
            }
        };
        return boost::apply_visitor(sub_visitor{}, lhs.data, rhs.data);
    }
    
    friend std::ostream& operator<<(std::ostream& os, WeirdVariant const& wv) {
        boost::apply_visitor(print_visitor(os), wv.data);
        return os;
    }
};


int main() {
    WeirdVariant lhs = std::string{"Hello "};
    WeirdVariant rhs = 6;
    std::cout << lhs + rhs + rhs << std::endl;
    std::cout << lhs + (rhs + rhs) << std::endl;
    lhs - rhs;
}
