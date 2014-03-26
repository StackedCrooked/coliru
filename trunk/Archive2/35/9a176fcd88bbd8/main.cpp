#if 0
<lots of text not including "label A" or "label B">    
label A: 34
<lots of text not including "label A" or "label B">
label B: 45
<lots of text not including "label A" or "label B">
...
#endif
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/repository/include/qi_seek.hpp>
#include <fstream>

namespace qi   = boost::spirit::qi;
namespace repo = boost::spirit::repository::qi;

int main()
{
    std::ifstream ifs("main.cpp");
    ifs >> std::noskipws;

    boost::spirit::istream_iterator f(ifs), l;

    std::vector<std::pair<char, int> > parsed;
    using namespace qi;
    bool ok = phrase_parse(
            f, l, 
            *repo::seek [ eol >> "label" >> char_("A-Z") >> ':' >> int_ ],
            blank,
            parsed
        );

    if (ok)
    {
        std::cout << "Found:\n";
        for (auto& p : parsed)
            std::cout << "'" << p.first << "' has value " << p.second << "\n";
    }
    else
        std::cout << "Fail at: '" << std::string(f,l) << "'\n";
}
