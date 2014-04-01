#include <boost/spirit/include/qi.hpp>

using V = boost::variant<int, double, std::string>;

struct my_struct : V { };

namespace boost { namespace spirit { namespace traits {

    template <typename Exposed, typename Domain>
    struct transform_attribute<Exposed, my_struct, Domain, void> :
        transform_attribute<Exposed, V, Domain, void> { 
            using base_type = transform_attribute<Exposed, V, Domain, void>;
            using typename base_type::type;

            //static type pre(Exposed& val)             { return base_type::pre(val); }
            //static void post(Exposed& val, type attr) { base_type::post(val, attr); }
            //static void fail(Exposed&e)               { base_type::fail(e); }
        };
} } }

int main()
{
    std::string const input("3.14151926");

    auto f(begin(input)), l(end(input));
    using namespace boost::spirit::qi;

    V parsed;
    bool ok = phrase_parse(
            f, l,
              lexeme [ '"' >> *~char_('"') >> '"' ]                // string
            | real_parser<double, strict_real_policies<double> >() // double
            | int_                                                 // well, int :)
        , space, parsed);

    return ok? 1 : 2;
}
