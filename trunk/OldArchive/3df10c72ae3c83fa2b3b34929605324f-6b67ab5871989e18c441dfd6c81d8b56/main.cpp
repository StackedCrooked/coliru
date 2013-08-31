#include <boost/program_options.hpp>

#include <iostream>

int main(int argc, char **argv) {

    namespace opts = boost::program_options;

    opts::options_description desc("EnsembleClustering options");
    desc.add_options()
            ("hello", "produce greeting");

    opts::variables_map vmap;
    opts::store(opts::parse_command_line(argc, argv, desc), vmap);
    opts::notify(vmap);

    if (vmap.count("hello")) {
        std::cout << "Hello World" << std::endl;
    }
}
