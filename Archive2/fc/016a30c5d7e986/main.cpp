#include <boost/program_options.hpp>

void tokenize(const std::string& str, std::vector<std::string>& tokens, const std::string& delimiters = ",")
{
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);

    // Find first non-delimiter.
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos) {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));

        // Skip delimiters.
        lastPos = str.find_first_not_of(delimiters, pos);

        // Find next non-delimiter.
        pos = str.find_first_of(delimiters, lastPos);
    }
}

namespace po = boost::program_options;

namespace lli {
    struct CommaSeparatedVector 
    {
        // comma separated values list
        std::vector<std::string> values;
    };

    // mapper for "lli::CommaSeparatedVector"
    std::istream& operator>>(std::istream& in, CommaSeparatedVector &value)
    {
        std::string token;
        in >> token;

        tokenize(token, value.values);

        return in;
    }

}

int main()
{
    po::options_description desc;
    lli::CommaSeparatedVector MAttrs;
    desc.add_options()
        ("mattr", po::value<lli::CommaSeparatedVector>(&MAttrs), "Target specific attributes (-mattr=help for details)");
}
