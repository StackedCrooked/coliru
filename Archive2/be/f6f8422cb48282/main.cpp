//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;

static std::string const sample = R"(
    {
        "arr" : [ { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\\u1ea4" }, "double" : 12.6e-3 },
                  "hello world\\n",
                  { }
                ],
        "folders" :
        [{
                "parent_id" : 110,
                "ignore1" : { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\\u1ea4" }, "double" : 12.6e-3 },
                "path" : "\/1\/105\/110\/",
                "ignore2" : { "prop2" : 2, "prop3" : { "arr_nested" : [2,3,4,5], "muhaha" : "\\u2ea4" }, "double" : 13.7e-2 },
                "ignore3" : { "prop3" : 3, "prop4" : { "arr_nested" : [3,4,5,6], "muhaha" : "\\u3ea4" }, "double" : 14.8e-1 },
                "id" : 109
            },
            "bogus",
            [ { "completely ignored": [] }, [], "", 0 ],
            {
                "ignore1" : { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\\u1ea4" }, "double" : 12.6e-3 },
                "path" : "\/1\/105\/",
                "ignore2" : { "prop2" : 2, "prop3" : { "arr_nested" : [2,3,4,5], "muhaha" : "\\u2ea4" }, "double" : 13.7e-2 },
                "parent_id" : 105,
                "id" : 110,
                "ignore3" : { "prop3" : 3, "prop4" : { "arr_nested" : [3,4,5,6], "muhaha" : "\\u3ea4" }, "double" : 14.8e-1 }
            }
        ],

        "more ignore" : [],

        "files" :
        [
            99e12, "woah",
            {
                "id"        : 26,
                "parent_id" : 105,
                "ANZR"      : "CVPGHER.CAT",
                "UNFU"      : "ZQ5_UNFU",
                "VQ"        : 26,
                "CNERAG_VQ" : 105,
                "name"      : "picture.png",
                "hash"      : "md5_hash",
                "path"      : "\/1\/105\/"
            },
            {
                "hash"      : "md5_hash",
                "UNFU"      : "ZQ5_UNFU",
                "id"        : 25,
                "VQ"        : 25,
                "name"      : "another_picture.jpg",
                "ANZR"      : "NABGURE_CVPGHER.WCT",
                "parent_id" : 110,
                "CNERAG_VQ" : 110,
                "path"      : "\/1\/105\/110\/",
                "CNGU"      : "\/1\/105\/110\/"
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

            // this is the actual basic JSON grammar, but ignoring all attributes:
            ignore_value  = ignore_obj | ignore_array | text_ | double_;
            ignore_member = text_ >> ':' >> ignore_value;
            ignore_obj    = '{' >> -(ignore_member % ',') >> '}';
            ignore_array  = '[' >> -(ignore_value  % ',') >> ']';

            // this is the adhoc grammar, but exploded with the exceptions to ignore:
            start    = '{' 
                       >> *((ignore_member - folders_ - files_) >> commasep)
                       >> (
                               (*((ignore_member - folders_ - files_) >> ',') >> folders_ >> commasep) ^
                               (*((ignore_member - folders_ - files_) >> ',') >> files_   >> commasep)
                          )
                       >> *((ignore_member - folders_ - files_) >> commasep)
                     >> '}';

            folders_ = key(+"folders") >> '[' >> -((folder_ | ignore_value) % ',') >> ']';
            files_   = key(+"files")   >> '[' >> -((file_   | ignore_value) % ',') >> ']';

            folder_  = '{' >> (
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path")) >> ',')) >> (key(+"id")        >> int_  >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path")) >> ',')) >> (key(+"parent_id") >> int_  >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path")) >> ',')) >> (key(+"path")      >> text_ >> commasep)
                        ) >> '}';
            file_    = '{' >> (
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path") - key(+"name") - key(+"hash")) >> ',')) >> (key(+"id")        >> int_  >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path") - key(+"name") - key(+"hash")) >> ',')) >> (key(+"parent_id") >> int_  >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path") - key(+"name") - key(+"hash")) >> ',')) >> (key(+"path")      >> text_ >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path") - key(+"name") - key(+"hash")) >> ',')) >> (key(+"name")      >> text_ >> commasep) ^
                            (*((ignore_member - key(+"id") - key(+"parent_id") - key(+"path") - key(+"name") - key(+"hash")) >> ',')) >> (key(+"hash")      >> text_ >> commasep)
                        ) >> '}';

            key      = lexeme ['"' >> lazy(_r1) >> '"'] >> ':';
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
            BOOST_SPIRIT_DEBUG_NODES((ignore_value)(ignore_member)(ignore_obj)(ignore_array))
        }
    private:
        qi::rule<It, Data(),            Skipper> start;
        qi::rule<It, Data::Files(),     Skipper> files_;
        qi::rule<It, Data::Folders(),   Skipper> folders_;
        qi::rule<It, Data::File(),      Skipper> file_;
        qi::rule<It, Data::Folder(),    Skipper> folder_;
        qi::rule<It, void(const char*), Skipper> key;

        qi::rule<It, std::string()> text_, ch_;
        qi::rule<It> commasep;
        qi::rule<It, Skipper> ignore_value, ignore_member, ignore_obj, ignore_array;

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
        if (e.id != 0)
            std::cout << "folder:\t" << e.id << "\t" << e.path << "\n";
    for (auto& e : parsed.files) 
        if (e.id != 0)
            std::cout << "file:\t"   << e.id << "\t" << e.path << "\t" << e.name << "\n";
}
