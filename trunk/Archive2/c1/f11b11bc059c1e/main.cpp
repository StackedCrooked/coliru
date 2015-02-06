#include <boost/fusion/adapted/struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/utility/string_ref.hpp>

namespace qi = boost::spirit::qi;
using sref   = boost::string_ref;

namespace boost { namespace spirit { namespace traits {
    template <typename It>
    struct assign_to_attribute_from_iterators<sref, It, void> {
        static void call(It f, It l, sref& attr) { attr = { f, size_t(std::distance(f,l)) }; }
    };
} } }

struct Line {
    sref name, city;
    long id;
};

BOOST_FUSION_ADAPT_STRUCT(Line, (sref,name)(long,id)(sref,city))

int main() {
    boost::iostreams::mapped_file_source mmap("input.txt");

    using namespace qi;

    std::vector<Line> parsed;
    parsed.reserve(32000000);
    if (phrase_parse(mmap.begin(), mmap.end(), 
                omit[+graph] >> eol >>
                (raw[*~char_(";\r\n")] >> ';' >> long_ >> ';' >> raw[*~char_(";\r\n")]) % eol,
                qi::blank, parsed))
    {
        std::cout << "Parsed " << parsed.size() << " lines\n";
    } else {
        std::cout << "Failed after " << parsed.size() << " lines\n";
    }

    std::cout << "Printing 10 random items:\n";
    for(int i=0; i<10; ++i) {
        auto& line = parsed[rand() % parsed.size()];
        std::cout << "city: '" << line.city << "', id: " << line.id << ", name: '" << line.name << "'\n";
    }
}
