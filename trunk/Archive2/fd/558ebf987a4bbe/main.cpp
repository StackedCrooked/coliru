#include <iostream>
#include <vector>
#include <string>

#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace boost { namespace program_options {
template <class charT>
void validate(boost::any& v, const std::vector<std::basic_string<charT> >& xs, unsigned int*, int)
{
    using namespace po::validators;
    std::cout << "validate is redefined" << std::endl;
    check_first_occurrence(v);
    std::basic_string<charT> s(get_single_string(xs));
    try {
        v = boost::any(boost::lexical_cast<unsigned int>(s));
    } catch (const boost::bad_lexical_cast&) {
        boost::throw_exception(invalid_option_value(s));
    }
}
}}

int main(int argc, char* argv[])
{
    po::options_description cmdLineOptions;
    po::variables_map vm;

    unsigned int v;
    const char* args[] = {"tst", "-k", "10"};

    cmdLineOptions.add_options()
        ("key,k", po::value<unsigned int>(&v)->required())
      ;

    po::store(po::command_line_parser(sizeof(args) / sizeof(args[0]), args).options(cmdLineOptions).run(), vm);
    po::notify(vm);

    std::cout << v << '\n';

    return 0;
}
