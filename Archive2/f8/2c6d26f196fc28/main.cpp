#include <array>
#include <streambuf>
#include <iostream>
#include <boost/utility/string_ref.hpp>
#include <string>

template<typename charT, typename traits>
class static_streambuf : public std::basic_streambuf<charT, traits>
{
public:
    using typename std::basic_streambuf<charT, traits>::char_type;

    static_streambuf(char_type* begin, char_type* end)
      : begin_(begin), end_(end)
    {
        this->setp(begin, end);
        this->setg(begin, begin, begin);
    }
    
    static_streambuf(const static_streambuf&) = default;
    static_streambuf(static_streambuf&&)      = default;
    
    char_type* data() noexcept
    {
        return begin_;
    }
    
    const char_type* data() const noexcept
    {
        return begin_;   
    }
    
    std::streamsize capacity() const noexcept
    {
        return end_ - begin_;
    }

protected:
    using typename std::basic_streambuf<charT, traits>::int_type;
    using typename std::basic_streambuf<charT, traits>::traits_type;

    int_type underflow() override
    {
        if (this->gptr() < this->pptr())
        {
            this->setg(begin_, this->gptr(), this->pptr());
            return traits_type::to_int_type(*(this->gptr()));
        }
        return traits_type::eof();
    }
    
    int_type overflow(int_type c) override
    {
        if (!traits_type::eq_int_type(c, traits_type::eof()))
        {
            if (this->pptr() == this->epptr())
            {
                return traits_type::eof();
            }
            *(this->pptr()) = traits_type::to_char_type(c);
            this->pbump(1);
            return c;        
        }
        return traits_type::not_eof(c);
    }
    
    std::streamsize xsputn(const char_type* s, std::streamsize n) override
    {
        std::streamsize avail = this->epptr() - this->pptr(); n = n < avail ? n : avail;
        using std::copy;
        copy(s, s + n, this->pptr());
        return n;
    }
    
private:
    char_type* begin_;
    char_type* end_;
};

int main(int argc, char* argv[])
{
    char buf[1024];
    static_streambuf<char, std::char_traits<char>> sb(std::begin(buf), std::end(buf));
    std::ostream os(&sb);    
    os << "Hello hello hello" << std::endl;    

//    static_streambuf<8> sb;

//    os << "Hello hello hello" << std::endl;
    
    return 0;
}
