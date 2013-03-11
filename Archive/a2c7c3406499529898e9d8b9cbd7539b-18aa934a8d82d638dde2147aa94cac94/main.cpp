#include <boost/lexical_cast.hpp>
#include <string>

int main(int argc, char **)
{
    throw boost::lexical_cast<std::string>(argc);
    throw boost::lexical_cast<std::string>(argc);
}