#include <boost/spirit/include/qi.hpp>
#include <fstream>

namespace qi   = boost::spirit::qi;

void ii(int const& i)
{
    std::cout << i << std::endl;
}

void dd(double const& d)
{
    printf("%f\n", d);
}

int main()
{
    std::string input("#location=addition work/0.2387/6664 area/0.0565/1577 source/0.0479/1338 place/0.0447/1248 center/0.0369/1031");
//    std::ifstream ifs("main.cpp");
//    ifs >> std::noskipws;

    std::string::iterator strbegin = input.begin();

    std::vector<double> parsed;
    using namespace qi;
    bool ok = phrase_parse(
            strbegin, input.end(),
            //grammar
                "#location=" >> char_
                | char_ >> "/" >> double_[&dd] >> "/" >> int_[&ii],
            blank,
            parsed
        );

    if (ok)
    {
        std::cout << "Found:\n";
        for (auto& p : parsed)
            std::cout << p << "\n";
    }
    else
        std::cout << "Fail at: '" << std::string(strbegin, input.end()) << "'\n";
}
