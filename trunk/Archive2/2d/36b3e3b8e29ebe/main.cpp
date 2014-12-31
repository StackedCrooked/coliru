#include <boost/variant.hpp>
#include <boost/make_shared.hpp>

namespace Tree {
    struct Data {
        double x,y,z;
    };

    using Node  = boost::make_recursive_variant<std::string, Data, std::vector<boost::recursive_variant_> >::type;
    using Nodes = std::vector<Node>;

    namespace Operations {
        struct reverser : boost::static_visitor<Node> {
            Node operator()(Node const& tree)       const { return apply_visitor(*this, tree); }
            Node operator()(Data const& d)          const { return Data {d.z, d.y, d.x}; }
            Node operator()(std::string const& s)   const { return std::string(s.rbegin(), s.rend()); }
            Node operator()(Nodes const& children)  const {
                Nodes revchildren;
                std::transform(children.rbegin(), children.rend(), back_inserter(revchildren), *this);
                return revchildren;
            }
        };

        Node reverse(Node const& tree) {
            return reverser()(tree);
        }
    }

    using Operations::reverse;
}

// For our demo, let's implement `operator <<` with a manipulator
#include <iostream>
namespace IO {
    namespace detail {
        using namespace boost;

        // this pretty prints the tree as C++ initializer code
        struct print_visitor : static_visitor<void> {
            print_visitor(std::ostream& os, std::string const& indent = "\n") : _os(os), _indent(indent) {}

            // concrete types
            void operator()(std::string const& s)  const { _os << '"' << s << '"'; }
            void operator()(Tree::Data const& d)   const { _os << "Data {" << d.x << "," << d.y << "," << d.z << '}'; }

            // generics to cater for both direct and shared tree nodes
            template <typename T>     void operator()(shared_ptr<T> const& sp)       const { (*this)(*sp); }
            template <typename T>     void operator()(shared_ptr<const T> const& sp) const { (*this)(*sp); }
            template <typename... Ts> void operator()(variant<Ts...> const& tree)    const { apply_visitor(*this, tree); }

            template <typename Node>
            void operator()(std::vector<Node> const& children) const {
                _os << "Nodes {";

                print_visitor subnode(_os, _indent + "  ");
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
        };

        template <typename NodeType>
        struct print_manip {
            print_manip(NodeType const& n) : _node(n) {}
            friend std::ostream& operator<<(std::ostream& os, print_manip const& m) {
                return print_visitor(os)(m._node), os << ";";
            }

            private:
            NodeType const& _node;
        };
    }

    template <typename NodeType>
        detail::print_manip<NodeType> print(NodeType const& node) { 
            return node; 
        }
}

namespace Support {
    namespace detail {
        template <typename SNode, typename Nodes = std::vector<SNode> >
        struct share_visitor : boost::static_visitor<SNode> {
            SNode operator()(Tree::Node const& tree)      const { return apply_visitor(*this, tree); }

            SNode operator()(Tree::Nodes const& children) const {
                Nodes shared;
                std::transform(children.begin(), children.end(), back_inserter(shared), *this);
                return boost::make_shared<typename SNode::element_type>(shared);
            }

            template <typename LeafNode>
            SNode operator()(LeafNode const& v) const { return boost::make_shared<typename SNode::element_type>(v); }
        };
    }
}

#include <boost/bind.hpp>

namespace SharedTree {
    using Tree::Data;

    using SNode = boost::shared_ptr<
            boost::make_recursive_variant<
                std::string, Data, std::vector<boost::shared_ptr<boost::recursive_variant_>
            > >::type>;

    using Node  = SNode::element_type;
    using Nodes = std::vector<SNode>;

    namespace Operations {
        template <typename SNode, typename Nodes = std::vector<SNode> >
        struct upper_caser : boost::static_visitor<SNode> {
            SNode operator()(SNode const& tree)            const { 
                return apply_visitor(boost::bind(*this, boost::ref(tree), _1), *tree); 
            }
            // dispatch
            SNode operator()(SNode const&, std::string const& value) const {
                std::string xformed;
                std::transform(value.begin(), value.end(), back_inserter(xformed), [](uint8_t c) { return std::toupper(c); });
                return boost::make_shared<typename SNode::element_type>(xformed);
            }
            SNode operator()(SNode const& node, Nodes const& children)  const {
                Nodes xformed; // TODO optimize
                std::transform(children.begin(), children.end(), back_inserter(xformed), *this);

                return (equal(children, xformed))
                    ? node
                    : boost::make_shared<typename SNode::element_type>(xformed);
            }
            template <typename V> SNode operator()(SNode const& node, V const&) const {
                return node;
            }
        };

        template <typename SNode>
        SNode ucase(SNode const& tree) {
            return upper_caser<SNode>()(tree);
        }
    }

    using Operations::ucase;

    SNode share(Tree::Node const& tree) {
        return Support::detail::share_visitor<SNode>()(tree);
    }
}

namespace CowTree {
    using Tree::Data;

    using SNode = boost::shared_ptr<
            boost::make_recursive_variant<
                std::string, Data, std::vector<boost::shared_ptr<boost::recursive_variant_ const>
            > >::type const>;

    using Node  = SNode::element_type;
    using Nodes = std::vector<SNode>;

    struct share_visitor : boost::static_visitor<SNode> {
        SNode operator()(Tree::Node const& tree)      const { return apply_visitor(*this, tree); }

        SNode operator()(Tree::Nodes const& children) const {
            Nodes shared;
            std::transform(children.begin(), children.end(), back_inserter(shared), *this);
            return boost::make_shared<Node>(shared);
        }

        template <typename LeafNode>
        SNode operator()(LeafNode const& v) const { return boost::make_shared<Node>(v); }
    };
    
    SNode share(Tree::Node const& tree) {
        return share_visitor()(tree);
    }
}

#include <boost/lexical_cast.hpp> // for the roundtrip test

namespace Support {
    template <typename NodeType1, typename NodeType2>
    bool tree_equal(NodeType1 const& a, NodeType2 const& b) {
        using IO::print;
        return boost::lexical_cast<std::string>(print(a)) == 
            boost::lexical_cast<std::string>(print(b));
    }
}

int main() {
    using namespace Tree;
    using IO::print;
    using Support::tree_equal;

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

    std::cout << "Before transformation: \n" << print(tree)          << "\n";
    std::cout << "After transformation:  \n" << print(reverse(tree)) << "\n";

    Node roundtrip = reverse(reverse(tree));
    std::cout << "Roundtrip tree_equal: "    << std::boolalpha       << tree_equal(tree, roundtrip) << "\n";

    std::cout << "//////////////////////////////////////////////////\n";
    std::cout << "// manipulate SharedTree \"copies\"\n";
    auto shared = SharedTree::share(tree);
    std::cout << "Shared: "          << print(shared)            << "\n";
    std::cout << "Equal to source: " << tree_equal(tree, shared) << "\n";

    using boost::get;
    using boost::make_shared;
    get<SharedTree::Nodes>(*shared).push_back(make_shared<SharedTree::Node>("added to a shared tree"));

    auto shared2 = shared;
    std::cout << "Shared2: "           << print(shared2)              << "\n";
    std::cout << "Shared tree_equal: " << tree_equal(shared, shared2) << "\n";
    std::cout << "Equal to source: "   << tree_equal(tree, shared)    << "\n";
    
    std::cout << "//////////////////////////////////////////////////\n";
    std::cout << "// now let's see about CowTree\n";
    auto cow = CowTree::share(tree);
    std::cout << "Cow: "                 << print(cow)            << "\n";
    std::cout << "Equal to source: "     << tree_equal(tree, cow) << "\n";

    auto ucased = SharedTree::ucase(cow);
    std::cout << "Ucased: "              << print(ucased)           << "\n";
    std::cout << "Equal to cow source: " << tree_equal(ucased, cow) << "\n";

   /*
    *    The 
    *
    *        Nodes {
    *            Data { 2,3,4 },
    *            Data { 3,4,5 },
    *            Data { 4,5,6 },
    *        },
    *
    *    subtree should still be shared, because it wasn't touched:
    */
    std::cout << "Subtree from ucased: " << print(get<CowTree::Nodes>(*get<CowTree::Nodes>(*ucased)[2])[1]) << "\n";
    std::cout << "Subtree from cow: "    << print(get<CowTree::Nodes>(*get<CowTree::Nodes>(*cow   )[2])[1]) << "\n";
    std::cout << "Subtrees match: "      << tree_equal(
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*ucased)[2])[1],
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*cow)   [2])[1])
        << "\n";
    // unchanged nodes should be shared:
    std::cout << "Subtrees shared: " << (
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*ucased)[2])[1].get() ==
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*cow)   [2])[1].get())
        << "\n";
    // changed nodes aren't shared:
    std::cout << "Siblings unshared: " << (
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*ucased)[2])[2].get() !=
            get<CowTree::Nodes>(*get<CowTree::Nodes>(*cow)   [2])[2].get())
        << "\n";
    std::cout << "Parents unshared: " << (
            get<CowTree::Nodes>(*ucased)[2].get() !=
            get<CowTree::Nodes>(*cow)   [2].get())
        << "\n";
    std::cout << "Roots unshared: " << ( ucased.get() != cow.get())
        << "\n";
}
