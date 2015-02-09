#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

istream& parseDocument( istream& input, int &data ) {
    input >> data;
    string extra;
    getline( input, extra );
    if(!extra.empty() || !input.eof() ) throw std::runtime_error("extra charaters after end of document");
    return input;
}

template< typename MutableBuffers >
size_t bad_case_of_read_some( MutableBuffers const& outbuf )
{
    return buffer_copy( outbuf, buffer("12345\n\0some bad next frame\0") );
}

size_t bad_case_of_read_until( boost::asio::streambuf& strbuf )
{
        auto buffers= strbuf.prepare( 1024 );
        size_t read= bad_case_of_read_some( buffers );
        strbuf.commit( read );
        return read;
}

int main()
{
    boost::asio::streambuf strbuf;
    
    bad_case_of_read_until( strbuf );

    int data;
    istream stream(&strbuf);

    parseDocument( stream, data ); // will fail here

    return 0;
}
