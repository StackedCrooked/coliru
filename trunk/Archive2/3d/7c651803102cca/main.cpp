#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <iostream>
#include <sstream>

int main() 
{
    using namespace boost::iostreams;
    using namespace std;
#if 0
    std::istringstream iss("hello world\n");

    filtering_streambuf<input> def;
    def.push(zlib_compressor());
    def.push(iss);
    boost::iostreams::copy(def, std::cout);
#else
    std::string const rawdata {'x', '\234', '\313', 'H', '\315', '\311', '\311', 'W', '(', '\317', '/', '\312', 'I', '\341', '\002', '\0', '\036', 'r', '\004', 'g' };
    std::istringstream iss(rawdata, std::ios::binary);

    filtering_streambuf<input> def;
    def.push(zlib_decompressor());
    def.push(iss);
    boost::iostreams::copy(def, std::cout);
#endif
}
