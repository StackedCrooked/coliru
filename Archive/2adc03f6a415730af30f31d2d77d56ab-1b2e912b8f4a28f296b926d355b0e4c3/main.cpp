#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <vector>

namespace po = boost::program_options;

int
main( int argc, char* argv[] )
{
    std::vector<std::string> input;
    po::options_description options("Options");
    options.add_options()
        ("-u", po::value<bool>(), "Write bytes from the input file to the standard output without delay as each is read.")
        ("file", po::value(&input), "input")
        ;

    po::positional_options_description file_options;
    file_options.add("file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(options).positional(file_options).run(), vm);
    po::notify(vm);

    bool immediate = false;
    if(vm.count("-u"))
        immediate = true;
    BOOST_FOREACH( const auto& i, input ) {
        std::cout << "file: " << i << std::endl;
    }
}