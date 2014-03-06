#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class io_buffer : public std::streambuf
{
public:
    io_buffer(std::ostream& os, int buf_size = 4)
        : os_(os), buffer(buf_size)
    {
        os_.clear();
        char* beg = buffer.data();
        setp(beg, beg + buffer.size() - 1); // <<<<<<<<<<
    }

    int_type overflow(int_type c)
    {
        if (os_ && !traits_type::eq_int_type(c, traits_type::eof()))
        {
            *pptr() = traits_type::to_char_type(c);
            pbump(1);

            if (flush())
            {
                pbump(-(pptr() - pbase()));  // <<<<<<<<<<
                return c;
            } else
                return traits_type::eof();
        }

        return traits_type::not_eof(c);
    }

    bool flush()
    {
        return os_.write(pbase(), pptr() - pbase());
    }

    int sync()
    {
        return flush() ? 0 : -1;
    }
private:
    std::ostream& os_;
    std::vector<char> buffer;
};

int main()
{
    std::ostringstream oss;
    io_buffer buf(oss);

    std::ostream os(&buf);
    std::string str("Hello, World");

    os << str << std::endl;   // <<<<<<<<<<
    std::cout << oss.str() << std::endl;
}