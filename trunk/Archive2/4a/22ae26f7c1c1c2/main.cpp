#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/spirit/include/qi.hpp>

using namespace std;
namespace asio = boost::asio;

using asio::buffers_begin;
using asio::buffers_end;

template <typename ConstBuffers>
size_t parseDocument(ConstBuffers const& buffers, int &data) {

    auto b(buffers_begin(buffers)), f=b, l(buffers_end(buffers));

    namespace qi = boost::spirit::qi;
    return qi::phrase_parse(f, l, qi::int_ >> '\0', qi::space, data)
        ? (f - b) 
        : 0; // only optionally consume
}

template <typename MutableBuffers> size_t 
    fake_read1(MutableBuffers const &outbuf) { return asio::buffer_copy(outbuf, asio::buffer("12345" "\0" "23", 8)); }

template <typename MutableBuffers> size_t 
    fake_read2(MutableBuffers const &outbuf) { return asio::buffer_copy(outbuf, asio::buffer("456" "\0", 4)); }

#define READ_UNTIL(/*boost::asio::streambuf &*/strbuf, fake_read) { \
    auto buffers = strbuf.prepare(1024); \
    size_t read = fake_read(buffers); \
    std::cout << "READ_UNTIL " #fake_read ": " << read << " bytes\n"; \
    strbuf.commit(read); \
}

size_t readuntil2(boost::asio::streambuf &strbuf) {

    std::cout << __PRETTY_FUNCTION__ << "\n";
    static int delay_fake_async_receive = 6;
    if (delay_fake_async_receive--)
        return 0;

    auto buffers = strbuf.prepare(1024);
    size_t read = fake_read2(buffers);
    std::cout << "read2: " << read << " bytes\n";
    strbuf.commit(read);
    return read;
}

#include <boost/range/algorithm.hpp>

int main() {
    // this is the tricky scenario:
    asio::streambuf strbuf;

    READ_UNTIL(strbuf, fake_read1);
    //READ_UNTIL(strbuf, fake_read2); // will happen later, now we're stuck with a partial second frame

    int data1=0, data2=0;

    strbuf.consume(parseDocument(strbuf.data(), data1));

    size_t consumed = 0;
    while (!(consumed = parseDocument(strbuf.data(), data2))) {
        READ_UNTIL(strbuf, fake_read2);
    }

    std::cout << "Yay: " << data1 << "\n";
    std::cout << "Yay: " << data2 << "\n";

    //asio::ip::tcp::iostream networkstream("localhost", "6767");
    std::cout << asio::ip::tcp::iostream("localhost", "6767").rdbuf();
}
