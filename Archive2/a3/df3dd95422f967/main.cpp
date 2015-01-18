#include <boost/fusion/adapted.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/iostreams/device/mapped_file.hpp>

namespace qi = boost::spirit::qi;

#if 1
    struct Point
    {
        float x,y;
    };

    BOOST_FUSION_ADAPT_STRUCT(Point, (float, x)(float, y))

    typedef std::vector<Point> data_t;
#else
    // there is no speed difference when parsing into a straight container
    // (only works with the spirit implementation)
    typedef std::vector<float> data_t;
#endif

int main()
{
#if 0
    std::cin.unsetf(std::ios::skipws);
    std::istreambuf_iterator<char> f_(std::cin), l_;

    const std::vector<char> v(f_, l_);
    auto f = v.data(), l = f+v.size();
#elif 1
    boost::iostreams::mapped_file mmap(
            "input.txt", 
            boost::iostreams::mapped_file::readonly);
    auto f = mmap.const_data();
    auto l = f + mmap.size();
#endif

    data_t data;
    data.reserve(11000000); // or whatever makes sense

    using namespace qi;
    bool ok = phrase_parse(f,l,*(double_ > ',' > double_), space, data);
    if (ok)   
        std::cout << "parse success\n";
    else 
        std::cerr << "parse failed: '" << std::string(f,l) << "'\n";

    if (f!=l) std::cerr << "trailing unparsed: '" << std::string(f,l) << "'\n";

    std::cout << "data.size():   " << data.size() << "\n";
}
