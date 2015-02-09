#include <iostream>
#include <utility>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/qi_match.hpp>

namespace asio = boost::asio;

std::istream &parseDocument(std::istream &is, int &data) {
    namespace qi = boost::spirit::qi;
    return is >> qi::match(qi::int_ >> '\0', data);
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

int main() {
    // this is the easy scenario:
    {
        asio::streambuf strbuf;

        READ_UNTIL(strbuf, fake_read1);
        READ_UNTIL(strbuf, fake_read2);

        int data1, data2;
        std::istream stream(&strbuf);

        parseDocument(stream, data1);
        parseDocument(stream, data2); // will fail here

        std::cout << "Yo: " << data1 << "\n";
        std::cout << "Yo: " << data2 << "\n";
    }

    // this is the tricky scenario:
    {
        asio::streambuf strbuf;

        READ_UNTIL(strbuf, fake_read1);
        //READ_UNTIL(strbuf, fake_read2); // will happen later, now we're stuck with a partial second frame

        int data1, data2;
        std::istream stream(&strbuf);

        parseDocument(stream, data1);

        while (!parseDocument(stream, data2)) {
            stream.clear();
            READ_UNTIL(strbuf, fake_read2);
        }

        std::cout << "Oops: " << data1 << "\n";
        std::cout << "Oops: " << data2 << "\n";
    }
}
