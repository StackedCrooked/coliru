
#include <cstddef>
#include <boost/tokenizer.hpp>

struct Example
{
    boost::tokenizer<boost::char_separator<char>> tokens;
    decltype (tokens.begin()) i;
};

int main() {}