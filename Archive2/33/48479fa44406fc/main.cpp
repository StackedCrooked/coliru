#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>
#include <iterator>

struct Edge : std::pair<int, int> {
};

std::istream& operator>>(std::istream& is, Edge& edge)
{
    using namespace boost::spirit::qi;
    return is >> match("src:" > int_ > '\t' > "dst:" > int_ >> eol, edge.first, edge.second);
}

namespace io = boost::iostreams;

int main()
{
    io::mapped_file_source csv("csv.txt.gz");

    io::stream<io::mapped_file_source> textstream(csv);
    io::filtering_istream fs;
    fs.push(io::gzip_decompressor{});
    fs.push(textstream);

    for (
            std::istream_iterator<Edge> it(fs >> std::noskipws), last;
            it != last;
            ++it)
    {
        std::cout << it->first << " to " << it->second << "\n";
    }
}

