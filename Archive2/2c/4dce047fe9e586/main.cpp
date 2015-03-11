#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;

struct Dimension {
    struct Value {
        enum Type { PARENT, CHILD, PIXEL } type;
        int value;

        friend std::ostream& operator<<(std::ostream& os, Value const& v) {
            switch(v.type) {
                case PARENT: return os << "[PARENT:" << v.value << "]";
                case CHILD:  return os << "[CHILD:"  << v.value << "]";
                case PIXEL:  return os << "[PIXEL:"  << v.value << "]";
            }
            return os << "?";
        }
    };

    Value mWidth, mHeight;
};

BOOST_FUSION_ADAPT_STRUCT(Dimension::Value, (Dimension::Value::Type, type)(int, value))
BOOST_FUSION_ADAPT_STRUCT(Dimension, (Dimension::Value, mWidth)(Dimension::Value, mHeight))

template <typename It, typename Skipper>
struct grammar : qi::grammar<It, Dimension(), Skipper>
{
    grammar() : grammar::base_type(start) {
        using namespace qi;

        start   = width_ ^ height_;
        width_  = lit("width")  >> ':' >> value_ >> ';';
        height_ = lit("height") >> ':' >> value_ >> ';';
        value_  =
            ( "_child"  >> attr(Dimension::Value::CHILD)  >> attr(0)
            | "_parent" >> attr(Dimension::Value::PARENT) >> attr(0)
            | eps       >> attr(Dimension::Value::PIXEL)  >> int_
            );

        BOOST_SPIRIT_DEBUG_NODES((start)(value_)(width_)(height_))
    }
  private:
    qi::rule<It, Dimension(), Skipper> start;
    qi::rule<It, Dimension::Value(), Skipper> value_, width_, height_;
};

int main() {
    using It = std::string::const_iterator;
    grammar<It, qi::space_type> p;

    for (std::string const input : {
            "width: 10;      height: _child;",
            "width: _parent; height: 10;",
            "width: _child;  height: 10;"
            })
    {
        It f = input.begin(), l = input.end();
        std::cout << "\n-----------------------------------\n"
                  << "Parsing '" << input << "'\n";

        Dimension parsed;
        bool ok = qi::phrase_parse(f, l, p, qi::space, parsed);

        if (ok)
            std::cout << "Parsed: (" << parsed.mWidth << "x" << parsed.mHeight << ")\n";
        else
            std::cout << "Parse failed\n";

        if (f!=l)
            std::cout << "Remaining input: '" << std::string(f,l) << "'\n";
    }
}
