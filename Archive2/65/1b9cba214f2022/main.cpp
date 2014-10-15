#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    int opt;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("optimization,O", po::value<int>(&opt)->default_value(1), "optimization level")
        ("include-path,I", po::value< std::vector<std::string> >(), "include path")
        ("input-file", po::value< std::vector<std::string> >(), "input file")
        ;

    po::variables_map vm;
    po::store(
            po::parse_command_line(argc, argv, desc, 
                po::command_line_style::allow_dash_for_short |
                po::command_line_style::allow_long |
                po::command_line_style::long_allow_adjacent |
                po::command_line_style::short_allow_adjacent | 
                po::command_line_style::allow_short
            ),
            vm);

    po::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    std::cout << "Optimization level chosen: " << opt << "\n";
}
