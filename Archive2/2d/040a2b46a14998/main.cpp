#include <iostream>
#include <cassert>
#include <limits>

template <class Inserter>
class filtering_streambuf : public std::streambuf
{
public:
    filtering_streambuf(std::streambuf* sbuf,
                        Inserter inserter,
                        bool delete_when_finished = false);
                        
    filtering_streambuf(std::streambuf* sbuf,
                        bool delete_when_finished = false);
                        
    ~filtering_streambuf();
                        
    int_type overflow(int_type c);
    int sync();
private:
    std::streambuf* m_sbuf;
    Inserter m_inserter;
    bool m_delete_when_finished;
};

template<class Inserter>
filtering_streambuf<Inserter>::filtering_streambuf(
    std::streambuf* sbuf,
    Inserter inserter,
    bool delete_when_finished)
    : m_sbuf(sbuf),
    m_inserter(inserter),
    m_delete_when_finished(delete_when_finished)
{ }

template<class Inserter>
filtering_streambuf<Inserter>::filtering_streambuf(
    std::streambuf* sbuf,
    bool delete_when_finished)
    : m_sbuf(sbuf),
    m_delete_when_finished(delete_when_finished)
{ }

template<class Inserter>
typename filtering_streambuf<Inserter>::int_type
filtering_streambuf<Inserter>::overflow(
        typename filtering_streambuf<Inserter>::int_type c)
{
    int_type result = traits_type::eof();
    if (c == traits_type::eof())
    {
        result = sync();
    }
    else if (m_sbuf != nullptr)
    {
        result = m_inserter(*m_sbuf, c);
        assert(0 <= result && result <= std::numeric_limits<char>::max());
    }
    return c;
}

template<class Inserter>
int filtering_streambuf<Inserter>::sync()
{
    return std::streambuf::sync();
}

template<class Inserter>
filtering_streambuf<Inserter>::~filtering_streambuf()
{
    sync();
    
    if (m_delete_when_finished)
        delete m_sbuf;
}

class line_inserter
{
public:
    line_inserter() : new_line(true) { }

    int operator()(std::streambuf& sbuf, int c)
    {
        int result = eof();
        if (c != eof() && new_line)
        {
            std::ostream(&sbuf) << ++line_number << ": ";
        }
        new_line = (c == '\n');
        
        return result != eof() ? result : sbuf.sputc(c);
    }
private:
    int line_number = 0;
    bool new_line;
    
    int eof() const { return std::char_traits<char>::eof(); }
};

int main()
{
    filtering_streambuf<line_inserter> linebuf(std::cout.rdbuf());
    std::ostream os(&linebuf);
    os << "Hello" << std::endl << "World";
}