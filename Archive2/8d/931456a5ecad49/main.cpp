#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char **argv) {
    // Declare the supported options.
    boost::program_options::options_description desc("Allowed options");

    std::string optRunTimeE;
    desc.add_options()
        ("help,h", "produce help message")
        ("RunTimeE", boost::program_options::value<std::string>(&optRunTimeE), "RunTimeE Version")
        ("rtttt",    boost::program_options::value<std::string>(&optRunTimeE), "RunTimeE Version")
        ;

    boost::program_options::variables_map vm;
    boost::program_options::store(
            boost::program_options::command_line_parser(argc, argv)
            .options(desc)
            .style(
                boost::program_options::command_line_style::unix_style |
                boost::program_options::command_line_style::allow_long_disguise)
            .run(),
            vm);

    boost::program_options::notify(vm);

    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 1;
    }

    if (vm.count("RunTimeE")) std::cout << "vm[RunTimeE]: " << vm["RunTimeE"].as<std::string>() << std::endl;
    if (vm.count("rtttt"))    std::cout << "vm[rtttt]:    " << vm["rtttt"].as<std::string>()    << std::endl;

    std::cout << "optRunTimeE: " << optRunTimeE << std::endl;
}
