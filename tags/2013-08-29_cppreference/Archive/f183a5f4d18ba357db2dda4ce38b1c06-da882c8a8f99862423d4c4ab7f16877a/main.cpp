#include <boost/spirit/include/karma.hpp>
#include <fstream>

namespace karma = boost::spirit::karma;

template <typename C>
void fillMyArray(C& data) 
{
    std::iota(begin(data), end(data), 0xf000);
}

int main()
{
    std::vector<boost::uint32_t> data(256);
    fillMyArray(data);

    std::ofstream output( "this.raw", std::ios_base::out | std::ios_base::binary | std::ios_base::trunc );
    boost::spirit::karma::ostream_iterator<char> outit(output);

    karma::generate(outit, +karma::big_word,    data);
    karma::generate(outit, +karma::little_word, data);
}