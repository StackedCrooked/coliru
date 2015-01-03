//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

static std::string const sample = R"(
    {
        "folders" :
        [{
                "id" : 109,
                "parent_id" : 110,
                "path" : "\/1\/105\/110\/"
            },
            {
                "id" : 110,
                "parent_id" : 105,
                "path" : "\/1\/105\/"
            }
        ],

        "files" :
        [{
                "id" : 26,
                "parent_id" : 105,
                "name" : "picture.png",
                "hash" : "md5_hash",
                "path" : "\/1\/105\/"
            },
            {
                "id" : 25,
                "parent_id" : 110,
                "name" : "another_picture.jpg",
                "hash" : "md5_hash",
                "path" : "\/1\/105\/110\/"
            }
        ]
    })";

struct Data {
    struct Folder { int id, parent_id; std::string path; };
    struct File   { int id, parent_id; std::string path, name, md5_hash; };

    using Folders = std::vector<Folder>;
    using Files   = std::vector<File>;

    Folders folders;
    Files   files;
};

BOOST_FUSION_ADAPT_STRUCT(Data::Folder, (int,id)(int,parent_id)(std::string,path))
BOOST_FUSION_ADAPT_STRUCT(Data::File,   (int,id)(int,parent_id)(std::string,path)(std::string,name)(std::string,md5_hash))
BOOST_FUSION_ADAPT_STRUCT(Data,         (Data::Folders,folders)(Data::Files,files))

namespace folder_info { // adhoc JSON parser

    template <typename It, typename Skipper = qi::space_type>
    struct grammar : qi::grammar<It, Data(), Skipper>
    {
        grammar() : grammar::base_type(start) {
            using namespace qi;

            start    = '{' >> 
                       (folders_ >> commasep) ^
                       (files_ >> commasep)
                     >> '}';

            folders_ = prop_key(+"folders") >> '[' >> -(folder_ % ',') >> ']';
            files_   = prop_key(+"files")   >> '[' >> -(file_   % ',') >> ']';

            folder_  = '{' >> (
                            (prop_key(+"id")        >> int_  >> commasep) ^
                            (prop_key(+"parent_id") >> int_  >> commasep) ^
                            (prop_key(+"path")      >> text_ >> commasep)
                        ) >> '}';
            file_    = '{' >> (
                            (prop_key(+"id")        >> int_  >> commasep) ^
                            (prop_key(+"parent_id") >> int_  >> commasep) ^
                            (prop_key(+"path")      >> text_ >> commasep) ^
                            (prop_key(+"name")      >> text_ >> commasep) ^
                            (prop_key(+"hash")      >> text_ >> commasep)
                        ) >> '}';

            prop_key = lexeme ['"' >> lazy(_r1) >> '"'] >> ':';
            commasep = &char_('}') | ',';

            ////////////////////////////////////////
            // Bonus: properly decoding the string:
            text_   = '"' >> *ch_ >> '"';

            ch_ = +(
                    ~char_("\"\\")) [ _val += _1 ] |
                       qi::lit("\x5C") >> (               // \ (reverse solidus)
                       qi::lit("\x22") [ _val += '"'  ] | // "    quotation mark  U+0022
                       qi::lit("\x5C") [ _val += '\\' ] | // \    reverse solidus U+005C
                       qi::lit("\x2F") [ _val += '/'  ] | // /    solidus         U+002F
                       qi::lit("\x62") [ _val += '\b' ] | // b    backspace       U+0008
                       qi::lit("\x66") [ _val += '\f' ] | // f    form feed       U+000C
                       qi::lit("\x6E") [ _val += '\n' ] | // n    line feed       U+000A
                       qi::lit("\x72") [ _val += '\r' ] | // r    carriage return U+000D
                       qi::lit("\x74") [ _val += '\t' ] | // t    tab             U+0009
                       qi::lit("\x75")                    // uXXXX                U+XXXX
                            >> _4HEXDIG [ append_utf8(qi::_val, qi::_1) ]
                    );

            BOOST_SPIRIT_DEBUG_NODES((files_)(folders_)(file_)(folder_)(start)(text_))
        }
    private:
        qi::rule<It, Data(),            Skipper> start;
        qi::rule<It, Data::Files(),     Skipper> files_;
        qi::rule<It, Data::Folders(),   Skipper> folders_;
        qi::rule<It, Data::File(),      Skipper> file_;
        qi::rule<It, Data::Folder(),    Skipper> folder_;
        qi::rule<It, void(const char*), Skipper> prop_key;

        qi::rule<It, std::string()> text_, ch_;
        qi::rule<It> commasep;

        struct append_utf8_f {
            template <typename...> struct result { typedef void type; };
            template <typename String, typename Codepoint>
            void operator()(String& to, Codepoint codepoint) const {
                auto out = std::back_inserter(to);
                boost::utf8_output_iterator<decltype(out)> convert(out);
                *convert++ = codepoint;
            }
        };
        boost::phoenix::function<append_utf8_f> append_utf8;
        qi::uint_parser<uint32_t, 16, 4, 4> _4HEXDIG;
    };

    template <typename Range, typename It = typename boost::range_iterator<Range const>::type>
    Data parse(Range const& input) {
        grammar<It> g;

        It first(boost::begin(input)), last(boost::end(input));
        Data parsed;
        bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);

        if (ok && (first == last))
            return parsed;

        throw std::runtime_error("Remaining unparsed: '" + std::string(first, last) + "'");
    }
}

using It = std::string::const_iterator;

int main()
{
    auto parsed = folder_info::parse(sample);

    for (auto& e : parsed.folders) 
        std::cout << "folder:\t" << e.id << "\t" << e.path << "\n";
    for (auto& e : parsed.files) 
        std::cout << "file:\t"   << e.id << "\t" << e.path << "\t" << e.name << "\n";
}
