#include <stdio.h>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>
#include <fstream>
#include <iostream>

namespace bios = boost::iostreams ;

struct ipipestream : bios::stream< bios::file_descriptor_source >
{
  using base = bios::stream< bios::file_descriptor_source > ;
  explicit ipipestream( const char* command ) : base( fileno(popen( command, "r" )), bios::close_handle ) {}
};

int main()
{
    ipipestream pout( "clang++ --version" ) ;
    std::cout << pout.rdbuf() ;
}
