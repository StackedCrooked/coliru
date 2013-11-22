#define BOOST_SPIRIT_DEBUG
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct identifier
{
    std::list<char> name;
    
    identifier() = default;

#if !defined(BE_OVERLY_GENERIC)
    explicit identifier(std::vector<char> const& name) 
        : name(begin(name), end(name))
    {}
#else
    template <typename Container>
        explicit identifier(Container const& name)
            : name(overly_generic_helper(name)) // implicit move
        {}
    
  private:
    // helper because we want ADL begin/end in the initialization list
    template <typename Container>
    static std::list<char> overly_generic_helper(Container const& name)
    {
        using std::begin; using std::end;
        return { begin(name), end(name) };
    }
#endif
};

// For BOOST_SPIRIT_DEBUG only:
static inline std::ostream& operator<<(std::ostream& os, identifier const& id) {
    return os << std::string(begin(id.name), end(id.name));
}

int main()
{
    typedef std::string::const_iterator It;
    using namespace qi;

    rule<It, identifier()> gr_identifier = 
        as<std::vector<char>>() [ (alpha | '_') >> *(alnum | '_') ];

    std::string input = "foo goo(hoo)";

    BOOST_SPIRIT_DEBUG_NODE(gr_identifier);

    It f(begin(input)), l(end(input));
    bool dummy = phrase_parse(f, l, gr_identifier, qi::space);

    return dummy? 0 : 255;
}

