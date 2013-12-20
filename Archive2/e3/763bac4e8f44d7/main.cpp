#include <string>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <boost/proto/core.hpp>
#include <boost/proto/transform.hpp>
#include <boost/type_traits/add_reference.hpp>
namespace proto = boost::proto;
using proto::_;

struct ptree_of_tag
{};

// A simple callable function object that inserts a
// (key,value) pair into a ptree.
struct insert
  : proto::callable
{
    template<typename Sig>
    struct result;

    template<typename This, typename Ptree, typename Key, typename Value>
    struct result<This(Ptree, Key, Value)>
      : boost::add_reference<Ptree>
    {};

    template<typename Ptree, typename Key, typename Value>
    Ptree &operator()(Ptree &tree, Key const &key, Value const &value) const
    {
        tree.put(key,value);
        return tree;
    }
};


// The grammar for valid ptree-list expressions, and a
// transform that populates the map.
struct PtreeOf
  : proto::or_<
        proto::when<
            // ptree_of(a,b)
            proto::function<
                proto::terminal<ptree_of_tag>
              , proto::terminal<_>
              , proto::terminal<_>
            >
          , insert(
                proto::_data
              , proto::_value(proto::_child1)
              , proto::_value(proto::_child2)
            )
        >
      , proto::when<
            // ptree_of(a,b)(c,d)...
            proto::function<
                PtreeOf
              , proto::terminal<_>
              , proto::terminal<_>
            >
          , insert(
                PtreeOf(proto::_child0)
              , proto::_value(proto::_child1)
              , proto::_value(proto::_child2)
            )
        >
    >
{};


template<typename Expr>
struct ptree_of_expr;

struct ptree_of_dom
  : proto::domain<proto::pod_generator<ptree_of_expr>, PtreeOf>
{};

// An expression wrapper that provides a conversion to a
// ptree that uses the PtreeOf
template<typename Expr>
struct ptree_of_expr
{
    BOOST_PROTO_BASIC_EXTENDS(Expr, ptree_of_expr, ptree_of_dom)
    BOOST_PROTO_EXTENDS_FUNCTION()

    template<typename Key, typename Value, typename Cmp>
    operator boost::property_tree::basic_ptree<Key, Value, Cmp> () const
    {
        BOOST_MPL_ASSERT((proto::matches<Expr, PtreeOf>));
        boost::property_tree::basic_ptree<Key, Value, Cmp> tree;
        return PtreeOf()(*this, 0, tree);
    }
};

ptree_of_expr<proto::terminal<ptree_of_tag>::type> const ptree_of = {{{}}};

int main()
{

    boost::property_tree::ptree pt =
        ptree_of("one", "value1")("one.two", "value2")("one.three", "value3");
    
    boost::property_tree::write_xml(std::cout, pt);

    return 0;
}