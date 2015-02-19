#include <array>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

namespace io = boost::iostreams;

int main()
{
    std::array<char, 128> buf;
    auto b = buf.begin(), e = buf.end();

    io::array_sink as(b, e);
    io::stream<io::array_sink> os(as);

    os << '1' << uint16_t(42) << uint32_t(42) << std::showbase << std::hex << int64_t(-1) << "\n" 
       << std::boolalpha << false << "\n"
       << std::numeric_limits<double>::infinity();

    std::cout << "result '" << std::string(b, os.tellp()) << "'\n";
}