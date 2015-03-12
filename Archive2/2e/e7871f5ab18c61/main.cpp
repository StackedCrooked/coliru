#include <boost/program_options.hpp>
#include <iostream>
#include <stdexcept>
#include <string>

namespace bpo = boost::program_options;

void conflicting_options(const bpo::variables_map& vm, 
                         const char* opt1, const char* opt2)
{
    if (vm.count(opt1) && !vm[opt1].defaulted() 
        && vm.count(opt2) && !vm[opt2].defaulted())
        throw std::logic_error(std::string("Conflicting options '") 
                               + opt1 + "' and '" + opt2 + "'.");
}

int main(int argc, char** argv)
{
  bpo::options_description desc;
  desc.add_options()
    ("frequency", bpo::value<int>(), "The frequency")
    ("wavelength", bpo::value<int>(), "The wavelength")
    ("energy", bpo::value<int>(), "The energy")
    ;

  bpo::variables_map vm;

  try {
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);

    conflicting_options(vm, "frequency", "wavelength");
    conflicting_options(vm, "frequency", "energy");
    conflicting_options(vm, "wavelength", "energy");

    auto print_if = [&vm](char const *opt) {
      if(vm.count(opt) && !vm[opt].defaulted()) {
        std::cout << opt << " = " << vm[opt].as<int>() << std::endl;
      }
    };

    print_if("frequency");
    print_if("wavelength");
    print_if("energy");

  } catch(std::exception const& e) {
    std::cerr << "Caught exception: " << e.what() << std::endl;

  }
}
