#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char** argv) {
    po::options_description desc("Allowed options");
    desc.add_options()
        ("include-path,I", po::value< std::vector<std::string> >(), "include path");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("include-path"))
    {
        std::vector<std::string> v = vm["include-path"].as< std::vector<std::string> >();
        std::cout << "Include paths are: ";
        for (auto& p : v)
            std::cout << "\n\t" << p;
    }
}
