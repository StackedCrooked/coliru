#include <boost/variant.hpp>
#include <map>

using nmap  = boost::make_recursive_variant<std::string, std::map<std::string, boost::recursive_variant_> >::type;
using map_t = std::map<std::string, nmap>;

#include <iostream>
static std::ostream& operator<<(std::ostream& os, nmap const& map);

int main()
{
    nmap my_map = map_t
    {
        { "a", "b" },
        { "c", map_t
            {
                { "d", "e" },
                { "f", map_t
                    {
                        { "most nested", "leaf node" },
                    } },
            } },
        };

    std::cout << my_map;
}

static std::ostream& operator<<(std::ostream& os, nmap const& map)
{
    struct print : boost::static_visitor<void>
    {
        print(std::ostream& os, int indent = 0) : os(os), indent(indent) { }

        void operator()(map_t const& map) const {
            os << "{";
            for(auto& item : map)
            {
                os << "\n";
                do_indent();
                os << "    " << item.first << ": ";
                boost::apply_visitor(print(os, indent+4), item.second);
            }
            if (!map.empty()) { os << "\n"; do_indent(); };
            os << "}";
        }

        void operator()(std::string const& str) const {
            os << str;
        }

    private:
        std::ostream& os;
        void do_indent() const { for (int n = indent; n>0; --n) os << ' '; }
        int indent = 0;
    };

    boost::apply_visitor(print(os), map);
    return os;
}

