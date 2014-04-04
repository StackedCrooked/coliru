#include <iostream>

namespace custom
{
    struct sep_impl
    {
        sep_impl(std::string const& separator);
        std::string separator;
    };
    
    sep_impl sep(std::string const& str)
    {
        return sep_impl(str);
    }
    
    std::ostream& nosep(std::ostream& os);
}

int separatorEnabled()
                      { static int idx = std::ios_base::xalloc(); return idx; }
int getSeparator()    { static int idx = std::ios_base::xalloc(); return idx; }

struct custom_separator : std::streambuf
{
public:
    custom_separator(std::ostream& _stream) : stream(_stream)
    { }
    
    int_type overflow(int_type c)
    {
        return stream.rdbuf()->sputc(c);
    }
    
    int sync()
    {
        if (stream.iword(separatorEnabled()))
        {
            void*& p = stream.pword(getSeparator());
            stream << *static_cast<std::string*>(p);
            return 0;
        }
        return stream.rdbuf()->pubsync();
    }
private:
    std::ostream& stream;
};

void cleanup(std::ios_base::event evt, std::ios_base& str, int idx)
{
    if (str.iword(separatorEnabled()) && evt == std::ios_base::erase_event)
    {
        void*& p = str.pword(idx);
        delete static_cast<std::string*>(p);
        str.iword(separatorEnabled()) = false; 
    }
}

std::ostream& set_separator(std::ostream& os, const custom::sep_impl& manip)
{
    if (!os.bad())
    {
        os.pword(getSeparator()) = new std::string(manip.separator);
        os.register_callback(cleanup, getSeparator());
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const custom::sep_impl& manip)
{
    std::ostream* p = os.tie();
    if (p)
    {
        set_separator(*p, manip);
        p->iword(separatorEnabled()) = true;
    }
    
    return os << std::unitbuf;
}

namespace custom
{
    sep_impl::sep_impl(std::string const& _sep) : separator(_sep) { }
    
    std::ostream& nosep(std::ostream& os)
    {
        os.tie()->iword(separatorEnabled()) = false;
        cleanup(std::ios_base::erase_event, os, getSeparator());
        os.tie(nullptr);
        return os << std::nounitbuf;
    }
    
    void install_separator(std::ostream& o1, std::ostream& o2)
    {
        static custom_separator csep(o2);
        o1.rdbuf(&csep);
        o1.tie(&o2);
    }
}

int main()
{
    std::ostream os(nullptr);
    custom::install_separator(os, std::cout);
    
    os << custom::sep(", ") << 4 << 2 << custom::nosep << 100 << 200 << 300;
}