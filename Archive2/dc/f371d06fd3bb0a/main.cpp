//#define BOOST_SPIRIT_DEBUG
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <map>

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
            object_ = '{' >> member_ % ',' >> '}';
            array_  = '[' >> value_  % ',' >> ']';

            BOOST_SPIRIT_DEBUG_NODES((text_)(value_)(member_)(object_)(array_))
        }
    private:
        qi::rule<It, text()>            text_;
        qi::rule<It, value(),  Skipper> value_;
        qi::rule<It, member(), Skipper> member_;
        qi::rule<It, object(), Skipper> object_;
        qi::rule<It, array(),  Skipper> array_;
    };

}

using It = std::string::const_iterator;

#include <boost/range/algorithm.hpp>
#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

struct Data {
    struct Folder { int id, parent_id; std::string path; };
    struct File   { int id, parent_id; std::string path, name, md5_hash; };

    using Folders = std::vector<Folder>;
    using Files   = std::vector<File>;

    Folders folders;
    Files   files;

    static Data extract_from(qd_json::value const& json) {
        using namespace boost::adaptors;

        return {
            boost::copy_range<Folders>(arr(obj(json).at("folders")) | transformed(obj) | transformed(&Data::extract_folder)),
            boost::copy_range<Files>  (arr(obj(json).at("files"))   | transformed(obj) | transformed(&Data::extract_file)),
        };
    }
 private:
    static Folder extract_folder(qd_json::object const& o) {
        return {
            id   (o.at("id")),
            id   (o.at("parent_id")),
            text (o.at("path"))
        };
    }
    static File extract_file(qd_json::object const& o) {
        return {
            id   (o.at("id")),
            id   (o.at("parent_id")),
            text (o.at("path")),
            text (o.at("name")),
            text (o.at("hash")),
        };
    }

    static int             id  (qd_json::value const&v) { return boost::get<double>(v); };
    static std::string     text(qd_json::value const&v) { return boost::get<qd_json::text>(v); };
    static qd_json::array  arr (qd_json::value const&v) { return boost::get<qd_json::array>(v); };
    static qd_json::object obj (qd_json::value const&v) { return boost::get<qd_json::object>(v); };
};

int main()
{
    qd_json::grammar<It> g;

    It first(sample.begin()), last(sample.end());
    qd_json::value parsed;
    bool ok = qi::phrase_parse(first, last, g, qi::space, parsed);

    if (ok)
    {
        std::cout << "Parsed sucessfully\n";
    } else
    {
        std::cout << "Parse failed\n";
    }

    if (first!=last)
        std::cout << "Remaining unparsed: '" << std::string(first, last) << "'\n";

    qd_json::value clone = parsed;
    assert(parsed == clone);

    auto extracted = Data::extract_from(parsed);

    std::cout << "extracted.folders[0].id: " << extracted.folders[0].id << "\n"; // T["folder"][0]["id"] would return "109" 
    std::cout << "extracted.files[0].name: " << extracted.files[0].name << "\n"; // T["files"][0]["name"] would return "logo.png"
}
