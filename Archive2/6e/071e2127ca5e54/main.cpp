#define BOOST_SPIRIT_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3
#define BOOST_SPIRIT_UNICODE
#if defined(_MSC_VER)
#   pragma warning (disable:4503) // decorated name length exceeded
#   pragma warning (disable:4996) // unchecked iterator
#endif

#include <iomanip>
#include "json.hpp"
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_function.hpp>
#include <boost/spirit/include/qi.hpp>
// unicode, please
#include <boost/regex/pending/unicode_iterator.hpp>

BOOST_FUSION_ADAPT_STRUCT(JSON::Object, (JSON::Object::values_t, values))
BOOST_FUSION_ADAPT_STRUCT(JSON::Array,  (JSON::Array ::values_t, values))

namespace JSON {
    Value& Object::operator[](std::string const& key)
    {
        auto match = std::find_if(begin(values), end(values), [&key](Entry const& e) { return key == e.first; });
        if (match != end(values))
            return match->second;

        values.push_back({ key, Undefined{} });
        return values.back().second;
    }

    Value const& Object::operator[](std::string const& key) const
    {
        auto match = std::find_if(begin(values), end(values), [&key](Entry const& e) { return key == e.first; });
        // argumentAssert(match != end(values), key);
        return match->second;
    }

    bool Object::has_key(std::string const& key) const
    {
        auto match = std::find_if(begin(values), end(values), [&key](Entry const& e) { return key == e.first; });
        return match != end(values);
    }

    namespace { namespace detail {
            std::string unicode_escape_(char ch) {
                std::ostringstream oss;
                oss << "\\u" << std::setw(4) << std::setfill('0') << std::hex << ((int) ch);
                return oss.str();
            }
            void append_utf8(std::string& to, uint32_t codepoint) {
                auto out = std::back_inserter(to);
                boost::utf8_output_iterator<decltype(out)> convert(out);
                *convert++ = codepoint;
            }
        }

        BOOST_PHOENIX_ADAPT_FUNCTION(std::string, unicode_escape_, detail::unicode_escape_, 1)
        BOOST_PHOENIX_ADAPT_FUNCTION(void,        append_utf8    , detail::append_utf8    , 2)
    }

    ///////////////////////////////////////////////////////////////
    // Qi Parser
    ///////////////////////////////////////////////////////////////

    namespace qi       = boost::spirit::qi;
    namespace encoding = qi::standard;

    template <typename It>
        struct skipper final : qi::grammar<It>
    {
        skipper() : skipper::base_type(rule) {}

        const qi::rule<It> rule = qi::space 
                | ("//" >> *~qi::char_("\n")   >> -qi::eol)
                | ("/*" >> *(qi::char_ - "*/") >> "*/")
                ;
    };

    template <typename It, typename Skipper>
        struct parser final : qi::grammar<It, Value(), Skipper>
    {
        parser() : parser::base_type(json)
        {
            truefalse.add
                ("true", Bool(true))
                ("false", Bool(false));

            // 2.1 values
            value = qi::attr_cast<Null>  (qi::lit("null")) 
                  | truefalse
                  | object
                  | array
                  | number
                  | string
                  ;

            // 2.2 objects
            object = '{' >> -(member % ',') >> '}';
            member = string >> ':' >> value;

            // 2.3 Arrays
            array = '[' >> -(value % ',') >> ']';

            // 2.4.  Numbers
            // Note our spirit grammar takes a shortcut, as the RFC specification is more restrictive:
            //
            // However non of the above affect any structure characters (:,{}[] and double quotes) so it doesn't
            // matter for the current purpose. For full compliance, this remains TODO:
            //
            //    Numeric values that cannot be represented as sequences of digits
            //    (such as Infinity and NaN) are not permitted.
            //     number = [ minus ] int [ frac ] [ exp ]
            //     decimal-point = %x2E       ; .
            //     digit1-9 = %x31-39         ; 1-9
            //     e = %x65 / %x45            ; e E
            //     exp = e [ minus / plus ] 1*DIGIT
            //     frac = decimal-point 1*DIGIT
            //     int = zero / ( digit1-9 *DIGIT )
            //     minus = %x2D               ; -
            //     plus = %x2B                ; +
            //     zero = %x30                ; 0
            const static qi::real_parser<Double>  ldbl = {};
            const static qi::int_parser <Integer> lint = {};
            number = qi::lexeme [ lint >> !qi::char_(".e0-9") ] | ldbl;

            // 2.5 Strings
            string = qi::lexeme [ '"' >> *char_ >> '"' ];

            static qi::uint_parser<uint32_t, 16, 4, 4> _4HEXDIG;

            char_ = +(
                    ~encoding::char_("\"\\")) [ qi::_val += qi::_1 ] |
                       qi::lit("\x5C") >> (                    // \ (reverse solidus)
                       qi::lit("\x22") [ qi::_val += '"'  ] | // "    quotation mark  U+0022
                       qi::lit("\x5C") [ qi::_val += '\\' ] | // \    reverse solidus U+005C
                       qi::lit("\x2F") [ qi::_val += '/'  ] | // /    solidus         U+002F
                       qi::lit("\x62") [ qi::_val += '\b' ] | // b    backspace       U+0008
                       qi::lit("\x66") [ qi::_val += '\f' ] | // f    form feed       U+000C
                       qi::lit("\x6E") [ qi::_val += '\n' ] | // n    line feed       U+000A
                       qi::lit("\x72") [ qi::_val += '\r' ] | // r    carriage return U+000D
                       qi::lit("\x74") [ qi::_val += '\t' ] | // t    tab             U+0009
                       qi::lit("\x75")                         // uXXXX                U+XXXX
                            >> _4HEXDIG [ append_utf8(qi::_val, qi::_1) ]
                    );

            // entry point
            json = value;

            BOOST_SPIRIT_DEBUG_NODES(
                    (json)(truefalse)(value)(object)(member)(array)(number)(string)(char_));
        }

      private:
        qi::symbols<char, Bool> truefalse;
        qi::rule<It, std::pair<std::string, Value>(),  Skipper> member;
        qi::rule<It, Value(),  Skipper> json, value;
        qi::rule<It, Object(), Skipper> object;
        qi::rule<It, Array(),  Skipper> array;
        //
        qi::rule<It, Value()>       number;
        qi::rule<It, std::string()> string;
        qi::rule<It, std::string()> char_;
    };

    ///////////////////////////////////////////////////////////////
    // Karma Generator
    ///////////////////////////////////////////////////////////////

    namespace karma      = boost::spirit::karma;
    template <typename It, typename Delimiter = qi::unused_type>
        struct generator : karma::grammar<It, Value(), Delimiter>
    {
        generator() : generator::base_type(json)
        {
            const static karma::int_generator <Integer> integer     = {};
            const static karma::real_generator<Double>  long_double = {};

            truefalse.add
                (Bool(false), "false")
                (Bool(true),  "true");

            value = karma::attr_cast<Null>  (karma::lit("null")) 
                  | truefalse
                  | object
                  | array
                  | integer
                  | long_double // TODO FIXME roundtrip safe formatting
                  | string
                  ;

            object = '{' << -(member % ',') << '}';
            member = string << ':' << value;

            array = '[' << -(value % ',') << ']';

            char_escape.add
                ('"',  "\\\"")
                ('\\', "\\\\")
              //('/',  "\\/")
                ('\b', "\\b")
                ('\f', "\\f")
                ('\n', "\\n")
                ('\r', "\\r")
                ('\t', "\\t");

            using karma::_val;
            using karma::_1;

            unicode_escape = 
                karma::eps(_val >= uint32_t(0x0) && _val <= uint32_t(0x1f)) << 
                encoding::string [ _1 = unicode_escape_(_val) ]
                ;

            char_ = char_escape | unicode_escape | encoding::char_;
            string = '"' << *char_ << '"';

            // entry point
            json = value;

            BOOST_SPIRIT_DEBUG_NODES( (json)(value)(object)(member)(array)(string)(char_)(unicode_escape));
        }

      private:
        karma::symbols<Bool, std::string> truefalse;
        karma::rule<It, std::pair<std::string, Value>(),  Delimiter> member;
        karma::rule<It, Value(),  Delimiter>  json, value;
        karma::rule<It, Object(), Delimiter>  object;
        karma::rule<It, Array(),  Delimiter>  array;
        //
        karma::rule<It,      std::string()> string;
        karma::rule<It,      char()>         char_;
        karma::rule<It,      uint32_t()>     unicode_escape;
        karma::symbols<char, std::string>   char_escape;
    };

    template <typename It>
    bool tryParseJson(It& f, It l, Value& value) // note: first iterator gets updated
    {
        static const skipper<It> s = {};
        static const parser<It, skipper<It> > p;

        try
        {
            return qi::phrase_parse(f,l,p,s,value);
        } catch(const qi::expectation_failure<It>& e)
        {
            std::string msg;

            boost::utf8_output_iterator<std::back_insert_iterator<std::string>> to_utf8(std::back_inserter(msg));
            // expectation points not currently used, but we could tidy up the
            // grammar to bail on unexpected tokens (future)
            std::copy(e.first, e.last, to_utf8); 

            std::cerr << e.what() << "'" << msg << "'\n";
            return false;
        }
    }

    template <typename It>
    bool tryParseJson(It& f, It l) // note: first iterator gets updated
    {
        Value discard;
        return tryParseJson(f,l,discard);
    }

    std::string to_string(Value const& json) {
        std::string text;
        auto out = std::back_inserter(text);

        static const generator<decltype(out)> g;
        karma::generate(out, g, json);

        return text;
    }

/*
 *    std::string to_string(Value const& json) {
 *        std::string result;
 *        auto out = std::back_inserter(result);
 *
 *        boost::utf8_output_iterator<decltype(out)> convert(out);
 *
 *        static const generator<decltype(convert)> g;
 *        karma::generate(convert, g, json);
 *
 *        return result;
 *    }
 */

    std::ostream& operator<<(std::ostream& os, Value const& v)
    {
        boost::spirit::ostream_iterator out(os);

        static const generator<decltype(out)> g;
        karma::generate(out, g, v);

        return os;
    }

    Value parse(std::string const& input) {
        auto f(begin(input)), saved = f, l(end(input));

        Value parsed;
        if (!tryParseJson(f, l, parsed))
        {
            std::cerr << "whoops at position #" << std::distance(saved, f) << "\n";
        }

        return parsed;
    }


    Value readFrom(std::istream& is)
    {
        is.unsetf(std::ios::skipws);
        boost::spirit::istream_iterator it(is), pte;

        Value parsed;
        if (!tryParseJson(it, pte, parsed))
        {
            std::cerr << "whoops"; // TODO
        }

        return parsed;
    }

    Value readFrom(std::istream&& is)
    {
        return readFrom(is);
    }

} // namespace JSON

