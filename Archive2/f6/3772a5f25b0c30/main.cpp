#include <iostream>
#include <vector>
#include <string>
#include <boost/program_options.hpp>
#include <boost/any.hpp>

struct catdog {
  catdog(std::string const& val):
    value(val)
  { }
  std::string value;
};

void validate(boost::any& v, 
              std::vector<std::string> const& values,
              catdog* /* target_type */,
              int)
{
  using namespace boost::program_options;

  // Make sure no previous assignment to 'v' was made.
  validators::check_first_occurrence(v);

  // Extract the first string from 'values'. If there is more than
  // one string, it's an error, and exception will be thrown.
  std::string const& s = validators::get_single_string(values);

  if (s == "cat" || s == "dog") {
    v = boost::any(catdog(s));
  } else {
    throw validation_error(validation_error::invalid_option_value);
  }
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    // Declare the supported options.
    po::options_description desc("Allowed options");
    desc.add_options()
        ("animal", po::value<catdog>(), "animal type")
        ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("animal")) {
        std::cout << "Animal type is " << vm["animal"].as<catdog>().value << ".\n";
    } else {
        std::cout << "No animal.\n";
    }
    return 0;
}