#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    if(argc<2)
    {
        printf("Too few arguments\n");
    }
    else
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
            ("c", "")
            ("d", "")
            ("filename", po::value<std::string>()->default_value(""));

        po::variables_map vm;
        po::store(po::parse_command_line(argc,argv,desc),vm);
        po::notify(vm);

        std::cout << "c parsed: "  << vm.count("c") << "\n";
        std::cout << "d parsed: "  << vm.count("d") << "\n";
        std::cout << "filename: '" << boost::any_cast<std::string>(vm["filename"].value()) << "'\n";
    }
}
