#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/bind.hpp>
#include <fstream>

namespace qi  = boost::spirit::qi;
namespace phx = boost::phoenix;

namespace demo {
    struct visitor : boost::static_visitor<> {
        template<typename Seq>
            void operator()(std::ostream& os, Seq const& seq) const {
                os << typeid(Seq).name() << "\t" << boost::fusion::as_vector(seq);
            }
    };
}

namespace data {
    struct Foo {
        Foo(std::string n="", int a=0) : name(n), age(a) {}

        std::string name;
        int age;
    };

    struct Bar {
        Bar(std::string l="") : location(l) {}

        std::string location;
    };

    using object  = boost::variant<Foo, Bar>;
    using objects = std::vector<object>;

    std::ostream& operator<< (std::ostream& os, object const& o) {
        boost::apply_visitor(boost::bind(demo::visitor(), boost::ref(os), _1), o);
        return os;
    }
}

BOOST_FUSION_ADAPT_STRUCT(data::Foo,(std::string,name)(int,age))
BOOST_FUSION_ADAPT_STRUCT(data::Bar,(std::string,location))

template <typename It>
struct grammar : qi::grammar<It, data::objects(), qi::blank_type> {
    grammar() : grammar::base_type(start) {
        using namespace qi;

        start   = *(label_(+"object") >> object_);
        object_ = foo_ | bar_;

        foo_    = "Foo" >> eol >> (
                    (string_prop_(+"name") >> eol) ^
                    (int_prop_(+"age") >> eol)
                );

        bar_    = "Bar" >> eol >> (
                    (string_prop_(+"location") >> eol)
                );

        label_  = lit(_r1) >> ':';

        string_prop_ = label_(_r1) >> lexeme [ *(char_ - eol) ];
        int_prop_    = label_(_r1) >> int_;
            
        BOOST_SPIRIT_DEBUG_NODES((start)(object_)(foo_)(bar_)(label_)(string_prop_)(int_prop_));
    }
  private:
    qi::rule<It, data::objects(), qi::blank_type> start;
    qi::rule<It, data::object(),  qi::blank_type> object_;
    qi::rule<It, data::Foo(),     qi::blank_type> foo_;
    qi::rule<It, data::Bar(),     qi::blank_type> bar_;

    qi::rule<It, std::string(std::string), qi::blank_type> string_prop_;
    qi::rule<It, int(std::string), qi::blank_type>         int_prop_;
    qi::rule<It, void(std::string), qi::blank_type>        label_;
};

int main()
{
    using It = boost::spirit::istream_iterator;
    std::ifstream ifs("input.txt");
    It f(ifs >> std::noskipws), l;

    grammar<It> p;
    data::objects parsed;
    bool ok = qi::phrase_parse(f,l,p,qi::blank,parsed);
    if (ok)
    {
        std::cout << "Parse success: " << parsed.size() << " objects\n";
        for(auto& object : parsed)
            std::cout << object << "\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (f!=l)
        std::cout << "Remaining unparsed input: '" << std::string(f,l) << "'\n";
}
