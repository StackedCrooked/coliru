#include <boost/program_options.hpp>
#include <boost/config.hpp>
#include <memory>
#include <iostream>

class Parser {

public:

  Parser();

  void add_all();
  void add_x_options();
  void add_y_options();
  void add_z_options();
  bool parse(int argc, char** argv);

  std::shared_ptr<boost::program_options::options_description> desc;
};


Parser::Parser() {
  desc = std::shared_ptr<boost::program_options::options_description>(new boost::program_options::options_description("Options"));
}

namespace config = boost::program_options;

void Parser::add_x_options() {
    //...
    desc->add_options()
        ("help",    "print usage instructions")
        ("option1", config::value<std::string>()->required())
        ("option2", config::value<std::string>()->required());
}

bool Parser::parse(int argc, char** argv) {
    config::variables_map vmap;

    try {
        config::store(config::parse_command_line(argc, argv, *desc), vmap);

        if (vmap.count("help")) {
            std::cout << *desc << std::endl;
            return false;
        }

        vmap.notify();
        return true;
    }
    catch(std::exception& e) {
        std::cout << "Error message: " << e.what() << "\n";
        return false;
    }
}

void do_test(std::initializer_list<const char*> args)
{
    std::string fake_program = "fake_program.exe";
    std::vector<char*> fake_argv { &fake_program[0] };
    for(auto&& arg : args)
        fake_argv.push_back(const_cast<char*>(arg));

    Parser parser;

    std::cout << "---------------------------------------------------------------------------\n";
    std::cout << "Test: ";
    for(auto const& a : fake_argv)
        std::cout << a << " ";
    std::cout << "\n";

    std::cout << "without add_x_options: ";
    parser.parse(fake_argv.size(), fake_argv.data());

    std::cout << "after add_x_options: ";
    parser.add_x_options();
    parser.parse(fake_argv.size(), fake_argv.data());
}

int main()
{
    do_test({ "--help" });
    do_test({ "--option1" });
    do_test({ "--option1", "value1" });
    do_test({ "--option2", "value2" });
    do_test({ "--option1", "value1", "--option2", "value2" });
}
