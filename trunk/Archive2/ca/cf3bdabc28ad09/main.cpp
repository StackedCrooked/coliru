#include <boost/io/ios_state.hpp>
#include <ios>
#include <iostream>
#include <ostream>

int  main()
{
    auto hex_printer = [](std::ostream& os, unsigned char byte) {
        boost::io::ios_flags_saver  ifs(os);
        os << std::hex << static_cast<unsigned>(byte) << ' ';
    };

    hex_printer(std::cout, 'A');
    std::cout << 42 << '\n';
}
