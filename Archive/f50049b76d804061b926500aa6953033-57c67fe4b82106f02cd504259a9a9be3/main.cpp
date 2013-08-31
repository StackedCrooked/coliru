#include <boost/program_options.hpp>
namespace po = boost::program_options;

int main (int argc, char *argv[])
{
    po::options_description config("Configuration");
    config.add_options()
                ("IPAddress,i", po::value<std::string>(), "IP Address")
                ("Port,p", po::value<std::string>(), "Port")
                ;

    try {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, config),vm);
        po::notify(vm);
        std::cout << "Values" << std::endl;

        const std::string address = vm["IPAddress"].as<std::string>();
        const std::string port = vm["Port"].as<std::string>();

        std::cout << "address: " << address << std::endl;
        std::cout << "port: " << port << std::endl;
    } catch ( const std::exception& e ) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}