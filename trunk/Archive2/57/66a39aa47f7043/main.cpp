//#define BOOST_SPIRIT_DEBUG
//#define BOOST_SPIRIT_USE_PHOENIX_V3
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <map>

namespace qi = boost::spirit::qi;

static std::string const sample = R"(
    {
        "arr" : [ { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\u1ea4" }, "double" : 12.6e-3 },
                    "hello world\n",
                    { }
                ],
        "folders" :
        [{
                "parent_id" : 110,
                "ignore1" : { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\u1ea4" }, "double" : 12.6e-3 },
                "path" : "/1/105/110/",
                "ignore2" : { "prop2" : 2, "prop3" : { "arr_nested" : [2,3,4,5], "muhaha" : "\u2ea4" }, "double" : 13.7e-2 },
                "ignore3" : { "prop3" : 3, "prop4" : { "arr_nested" : [3,4,5,6], "muhaha" : "\u3ea4" }, "double" : 14.8e-1 },
                "id" : 109
            },
            "bogus",
            [ { "completely ignored": [] }, [], "", 0 ],
            {
                "ignore1" : { "prop1" : 1, "prop2" : { "arr_nested" : [1,2,3,4], "muhaha" : "\u1ea4" }, "double" : 12.6e-3 },
                "path" : "/1/105/",
                "ignore2" : { "prop2" : 2, "prop3" : { "arr_nested" : [2,3,4,5], "muhaha" : "\u2ea4" }, "double" : 13.7e-2 },
                "parent_id" : 105,
                "id" : 110,
                "ignore3" : { "prop3" : 3, "prop4" : { "arr_nested" : [3,4,5,6], "muhaha" : "\u3ea4" }, "double" : 14.8e-1 }
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
                "path"      : "/1/105/"
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
                "path"      : "/1/105/110/",
                "CNGU"      : "/1/105/110/"
            }
        ]
    })";

namespace qd_json { // quick and dirty JSON handling
    using text   = std::string;
    using value  = boost::make_recursive_variant<
            text,                                      // "string" (roughly!)
            double,                                    // number
            std::map<text, boost::recursive_variant_>, // object
            std::vector<boost::recursive_variant_>     // array
        >::type;
    using member = std::pair<text, value>;
    using object = std::map<text, value>;
    using array  = std::vector<value>;

    template <typename It, typename Skipper = qi::space_type>
    struct grammar : qi::grammar<It, value(), Skipper>
    {
        grammar() : grammar::base_type(value_) {
            using namespace qi;

            text_   = '"' >> raw [*('\\' >> char_ | ~char_('"'))] >> '"';
            value_  = text_ | double_ | object_ | array_;
            member_ = text_ >> ':' >> value_;
            object_ = '{' >> -(member_ % ',') >> '}';
            array_  = '[' >> -(value_  % ',') >> ']';

            ////////////////////////////////////////
            // Bonus: properly decoding the string:
            text_   = lexeme [ '"' >> *ch_ >> '"' ];

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

            BOOST_SPIRIT_DEBUG_NODES((text_)(value_)(member_)(object_)(array_))
        }
    private:
        qi::rule<It, text()>            text_, ch_;
        qi::rule<It, value(),  Skipper> value_;
        qi::rule<It, member(), Skipper> member_;
        qi::rule<It, object(), Skipper> object_;
        qi::rule<It, array(),  Skipper> array_;

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
    value parse(Range const& input) {
        grammar<It> g;

        It first(boost::begin(input)), last(boost::end(input));
        value parsed;
        bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);

        if (ok && (first == last))
            return parsed;

        throw std::runtime_error("Remaining unparsed: '" + std::string(first, last) + "'");
    }
}

using It = std::string::const_iterator;

#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

struct Data {
    struct Folder { int id, parent_id; std::string path; };
    struct File   { int id, parent_id; std::string path, name, md5_hash; };

    using Folders = std::vector<Folder>;
    using Files   = std::vector<File>;

    Folders folders;
    Files   files;

    static Data extract_from(qd_json::value const& json) {
        Data result;

        try {
            for (auto const& v : arr(obj(json).at("folders"))) {
                try { result.folders.push_back(extract_folder(obj(v))); }
                catch(...) { }
            }
        } catch (...) { }

        try {
            for (auto const& v : arr(obj(json).at("files"))) {
                try { result.files.push_back(extract_file(obj(v))); }
                catch(...) { }
            }
        } catch (...) { }

        return result;
    }
 private:
    static Folder extract_folder(qd_json::object const& obj) {
        return {
            id   (obj.at("id")),
            id   (obj.at("parent_id")),
            text (obj.at("path"))
        };
    }
    static File extract_file(qd_json::object const& obj) {
        return {
            id   (obj.at("id")),
            id   (obj.at("parent_id")),
            text (obj.at("path")),
            text (obj.at("name")),
            text (obj.at("hash")),
        };
    }

    static int             id  (qd_json::value const&v) { return boost::get<double>(v); };
    static std::string     text(qd_json::value const&v) { return boost::get<qd_json::text>(v); };
    static qd_json::array  arr (qd_json::value const&v) { return boost::get<qd_json::array>(v); };
    static qd_json::object obj (qd_json::value const&v) { return boost::get<qd_json::object>(v); };
};

int main()
{
    auto json = qd_json::parse(sample);

    // compare json documents
    qd_json::value clone = json;
    assert(json == clone);

    // extract into user friendly datastructure from the question:
    auto extracted = Data::extract_from(json);

    for (auto& e : extracted.folders) std::cout << "folder:\t" << e.id << "\t" << e.path << "\n";
    for (auto& e : extracted.files)   std::cout << "file:\t"   << e.id << "\t" << e.path << "\t" << e.name << "\n";
}