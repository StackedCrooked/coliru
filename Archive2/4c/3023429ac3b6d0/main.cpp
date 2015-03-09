#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/set.hpp>
#include <boost/serialization/map.hpp>

#if 1
#   define DEMO_FLYWEIGHT
#   include <boost/flyweight/serialize.hpp>
#   include <boost/flyweight.hpp>
#endif

struct structure_element { 
    virtual ~structure_element() {}
    
  private:
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& /*ar*/, unsigned /*version*/) {
    }
};

namespace detail {
    struct symbol_impl {
        symbol_impl(std::string const& x) : _x(x) { }

#ifdef DEMO_FLYWEIGHT
        size_t hash() const { return boost::hash_value(_x); }
        //bool operator< (symbol_impl const& other) const { return _x <  other._x; }
        bool operator==(symbol_impl const& other) const { return _x == other._x; }
#endif

      private:
        std::string _x;

        friend class boost::serialization::access;
        template <typename Ar> void serialize(Ar& ar, unsigned /*version*/) {
            ar & _x;
        }
    };
}

#ifdef DEMO_FLYWEIGHT
namespace boost {
    template <> struct hash<::detail::symbol_impl> {
        size_t operator()(::detail::symbol_impl const& s) const { return s.hash(); }
    };
}
#endif

struct symbol : public structure_element {
    symbol(std::string const& x) : _impl(x) {}

  private:
#ifdef DEMO_FLYWEIGHT
    boost::flyweight<detail::symbol_impl> _impl;
#else
    detail::symbol_impl _impl;
#endif
    
    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned /*version*/) {
        ar & boost::serialization::base_object<structure_element>(*this);
        ar & _impl;
    }
};

struct structure_node : public structure_element {
    structure_node(std::set<symbol*> a, std::vector<structure_element*> c) 
        : some_attributes(std::move(a)), children(std::move(c))
    {
    }

    // TODO value semantics/ownership
  private:
    std::set<symbol *> some_attributes;
    std::vector<structure_element *> children;

    friend class boost::serialization::access;
    template <typename Ar> void serialize(Ar& ar, unsigned /*version*/) {
        ar & boost::serialization::base_object<structure_element>(*this);
        ar & some_attributes;
        ar & children;
    }
};

#include <boost/make_shared.hpp>

int main() {
    // everything is leaked, by design
    symbol* bar = new symbol("bar");

    structure_node data { 
        {
            new symbol("foo"),
            bar,
            new symbol("foo"),
            new symbol("foo"),
            bar,
        },
        { 
            bar,
        }
    };

    boost::archive::text_oarchive oa(std::cout);
    oa << data;
}
