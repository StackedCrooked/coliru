#include <streambuf>
#include <iostream>

class stream_redirector {
public:
    stream_redirector(std::ios& stream, std::streambuf* newBuf) :
        savedBuf_(stream.rdbuf()), stream_(stream)
    {
        stream_.rdbuf(newBuf);
    }

    ~stream_redirector() {
        stream_.rdbuf(savedBuf_);
    }

private:
    std::streambuf* savedBuf_;
    std::ios& stream_;
};

template <class cT, class traits = std::char_traits<cT> >
class basic_nullbuf: public std::basic_streambuf<cT, traits> {
    typename traits::int_type overflow(typename traits::int_type c)
    {
        return traits::not_eof(c); // indicate success
    }
};

template <class cT, class traits = std::char_traits<cT> >
class basic_onullstream: public std::basic_ostream<cT, traits> {
public:
    basic_onullstream():
    std::basic_ios<cT, traits>(&m_sbuf),
    std::basic_ostream<cT, traits>(&m_sbuf)
    {
        this->init(&m_sbuf);
    }

private:
    basic_nullbuf<cT, traits> m_sbuf;
};

typedef basic_onullstream<char> onullstream;
typedef basic_onullstream<wchar_t> wonullstream;

int main(int argc, char** argv)
{
    std::cerr << "foo" << std::endl;
    {
        onullstream nos;
        stream_redirector sr( std::cerr, nos.rdbuf() );
        std::cerr << "bar" << std::endl;
    }
    std::cerr << "baz" << std::endl;
}
