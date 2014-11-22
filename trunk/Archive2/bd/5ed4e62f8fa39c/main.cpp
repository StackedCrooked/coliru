#include <iostream>
#include <vector>
#include <string>

#include <boost/any.hpp>
#include <boost/strong_typedef.hpp>
#include <boost/program_options.hpp>

BOOST_STRONG_TYPEDEF(unsigned, Unsigned)

template<class charT>
    void validate(boost::any& v, 
            const std::vector< std::basic_string<charT> >& xs, 
            Unsigned* p, int)
    {
        std::cout << "validate is redefined" << std::endl;
        // do something else
    }

namespace po = boost::program_options;

int main()
{
    po::options_description cmdLineOptions;
    po::variables_map vm;

    Unsigned v;
    const char* args[] = {"tst", "-k", "10"};

    cmdLineOptions.add_options()
        ("key,k", po::value<Unsigned>(&v)->required())
      ;

    po::store(po::command_line_parser(sizeof(args) / sizeof(args[0]), args).options(cmdLineOptions).run(), vm);
    po::notify(vm);

    std::cout << v << '\n';

    return 0;
}
