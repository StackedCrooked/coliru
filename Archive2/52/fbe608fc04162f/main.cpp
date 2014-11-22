#include <iostream>
#include <vector>
#include <string>

#include <boost/program_options.hpp>

template<class charT>
    void validate(boost::any& v, 
            const std::vector< std::basic_string<charT> >& xs, 
            unsigned int* p, int)
    {
        std::cout << "validate is redefined" << std::endl;
        // do something else
    }

namespace po = boost::program_options;

int main()
{
    po::options_description cmdLineOptions;
    po::variables_map vm;

    unsigned int v;
    const char* args[] = {"tst", "-k", "10"};

    cmdLineOptions.add_options()
        ("key,k", po::value<unsigned int>(&v)->required())
      ;

    po::store(po::command_line_parser(sizeof(args) / sizeof(args[0]), args).options(cmdLineOptions).run(), vm);
    po::notify(vm);

    std::cout << v << '\n';

    return 0;
}
