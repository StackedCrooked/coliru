#include <boost/variant.hpp>

namespace Tree {
    using namespace boost;

    struct Data {
        double x,y,z;
    };

    using Node = make_recursive_variant<std::string, Data, std::vector<recursive_variant_> >::type;
    using Nodes = std::vector<Node>;

    struct reverser : static_visitor<Node> {
        Node operator()(Node const& tree)      const { return apply_visitor(*this, tree); }
        Node operator()(std::string const& s)  const { return std::string(s.rbegin(), s.rend()); }
        Node operator()(Data const& d)         const { return Data {d.z, d.y, d.x}; }
        Node operator()(Nodes const& children) const {
            Nodes revchildren;
            std::transform(children.rbegin(), children.rend(), back_inserter(revchildren), *this);
            return revchildren;
        }
    };
    
    Node reverse(Node const& tree) {
        return reverser()(tree);
    }
}

// For our demo, let's implement `operator <<`
#include <iostream>
namespace Tree {
    // this pretty prints the tree as C++ initializer code
    std::ostream& operator<<(std::ostream& os, Node const& node) {
        struct printer : static_visitor<void> {
            printer(std::ostream& os, std::string const& indent = "\n") : _os(os), _indent(indent) {}

            void operator()(Node const& tree)      const { apply_visitor(*this, tree); }
            void operator()(std::string const& s)  const { _os << '"' << s << '"'; }
            void operator()(Data const& d)         const { _os << "Data {" << d.x << "," << d.y << "," << d.z << '}'; }
            void operator()(Nodes const& children) const {
                _os << "Nodes {";

                printer subnode(_os, _indent + "  ");
                for(auto& n : children) {
                    _os << subnode._indent;
                    subnode(n);
                    _os << ",";
                }

                _os << _indent << '}';
            }
        private:
            std::ostream& _os;
            mutable std::string _indent;
        } p(os);
        return p(node), os << ";";
    }
}

#include <boost/lexical_cast.hpp> // for the roundtrip test

int main() {
    using namespace Tree;

    Node tree = Nodes {
        "hello",
        Data { 1,2,3 },
        Nodes {
            "more nested",
            Nodes {
                Data { 2,3,4 },
                Data { 3,4,5 },
                Data { 4,5,6 },
            },
            "nodes"
        }
    };

    std::cout << "Before transformation: \n" << tree << "\n";
    std::cout << "After transformation:  \n" << reverse(tree) << "\n";

    Node roundtrip = reverse(reverse(tree));

    std::cout << "Roundtrip equal: "<< std::boolalpha << (boost::lexical_cast<std::string>(tree) == boost::lexical_cast<std::string>(roundtrip));
}
