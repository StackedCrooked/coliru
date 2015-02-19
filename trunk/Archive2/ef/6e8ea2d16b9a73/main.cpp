#include <array>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <iostream>

namespace io = boost::iostreams;

int main()
{
    std::string buf;
    io::stream<io::back_insert_device<std::string> > os(io::back_inserter(buf));

    os << '1' << uint16_t(42) << uint32_t(42) << std::showbase << std::hex << int64_t(-1) << "\n" 
       << std::boolalpha << false << "\n"
       << std::numeric_limits<double>::infinity();

    os.flush();

    std::cout << "result '" << buf << "'\n";
}

