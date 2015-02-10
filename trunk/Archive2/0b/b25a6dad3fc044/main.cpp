#include <iostream>
#include <utility>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <boost/asio.hpp>

using namespace std;
using namespace boost::asio;

istream& parseDocument( istream& input, int &data ) { // some 3rd party parsers 
    input >> data;
    string extra;
    getline( input, extra );
    if(!extra.empty() || !input.eof() ) throw std::runtime_error("extra charaters after end of document");
    return input;
}

template< typename MutableBuffers >
size_t bad_case_of_read_some( MutableBuffers const& outbuf ){ // mocked read_some
    static int state=0;
    switch( state++ ) {
    case 0:
        return buffer_copy( outbuf, buffer("12345" "\0" "555", 10) );
    case 1:
        return buffer_copy( outbuf, buffer("55" "\0" "987654321" "\0" "321" "\0" "6", 18 ) );
    case 2:
        return buffer_copy( outbuf, buffer("66",2) );
    case 5:
        return buffer_copy( outbuf, buffer("666" "\0",4) );
    default:
        return 0;
    };
}

template< typename BufferIterator  >
std::pair< size_t, size_t > scanForFrames( BufferIterator read_begin, BufferIterator read_end, vector< std::pair< size_t, size_t > > &frames, char delim ) {
    auto frame_begin= read_begin;
    auto frame_end= read_begin;
    while(frame_end != read_end) {
        if( *frame_end != delim ) {
            ++frame_end;
            continue;
        }
        frames.push_back(std::make_pair(frame_end-read_begin, frame_begin-read_begin));
        read_begin= frame_begin= frame_end;
        while( ++frame_begin != read_end ) {
            if( *frame_begin != delim ) break;
        }
        frame_end = frame_begin;
    }
    return std::make_pair(frame_end-read_begin, frame_begin-read_begin);
}

size_t read_some_frames( boost::asio::streambuf& strbuf, std::function< void(istream&) > parser ) {
        auto buffers= strbuf.prepare( 1024 );
        size_t read= bad_case_of_read_some( buffers );

        vector< std::pair< size_t, size_t > > frames;
        std::pair< size_t, size_t > leftover= scanForFrames( buffers_begin(buffers), buffers_begin(buffers)+read, frames, '\0' );

        for( auto const& frame: frames ) {
            cout << "Frame size: " << frame.first << " skip:" << frame.second << endl;
            strbuf.commit( frame.first );
            strbuf.consume( frame.second );
            iostream stream( &strbuf );
            parser( stream );
        }
        cout << "Unfinished frame size: " << leftover.first << " skip:" << leftover.second << endl;
        strbuf.commit( leftover.first );
        strbuf.consume( leftover.second );
        return read;
}

int main()
{
    boost::asio::streambuf strbuf;

    for( int framecount=0 ; framecount < 6; )
        read_some_frames( strbuf, [&framecount](istream& input) {
            int data;
            parseDocument(input,data);
            cout << ++framecount << " parsed document: " << data << endl;
        } );

    return 0;
}