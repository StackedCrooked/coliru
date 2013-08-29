#ifndef LOGGER_H_INC_
#define LOGGER_H_INC_

#include <iostream>
#include <streambuf>
#include <vector>
#include <fstream>

class logger: public std::streambuf {
public:
    logger(std::streambuf* s): sbuf(s) {}
    ~logger() { overflow('\n'); }
private:
    typedef std::basic_string<char_type> string;

    int_type overflow(int_type c) {

        if (traits_type::eq_int_type(traits_type::eof(), c))
            return traits_type::not_eof(c);
        switch (c) {
        case '\n':
        case '\r':  {
            prefix = "[FIX]";
            buffer += c;
            if (buffer.size() > 1)
                sbuf->sputn(prefix.c_str(), prefix.size());
            int_type rc = sbuf->sputn(buffer.c_str(), buffer.size());
            buffer.clear();
            return rc;
        }
        default:
            buffer += c;
            return c;
        }
    }

    std::string prefix;
    std::streambuf* sbuf;
    string buffer;
};

namespace multi {
    class buf : public std::streambuf {
        std::vector<std::streambuf *> buffers;
    public:
        typedef std::char_traits<char> traits_type;
        typedef traits_type::int_type  int_type;
        
        buf() {}

        void attach(std::streambuf *s) { buffers.push_back(s); }
        void attach(std::ofstream &s) {    buffers.push_back(s.rdbuf()); }

        int_type overflow(int_type c) {
            bool eof = false;
            for (std::streambuf *buf : buffers)
                eof |= (buf->sputc(c) == traits_type::eof());
            return eof ? traits_type::eof() : c;
        }
    };

    class logstream : private logger, public std::ostream {
        std::vector<std::ofstream *> streams;
        buf outputs;
        
        void attach(std::ostream &s) { outputs.attach(s.rdbuf()); }
        void attach(char const *name) {
            std::ofstream *s = new std::ofstream(name);
            streams.push_back(s);
            outputs.attach(s->rdbuf());
        }

        template <typename T, typename...pack>
        void attach(T &t, pack&...p) {
            attach(t);
            attach(p...);
        }

    public:	
        template <typename...pack>
        logstream(pack&...p) : logger(&outputs), std::ostream(this) { attach(p...); }
        
        ~logstream() {
            for (auto d : streams) {
                d->close();
                delete d;
            }
        }
    };
}

#endif

    ///#include "logger.h"

    int main(){
        multi::logstream l(std::cout, std::cerr, "foo");
        l << "This is a prefixed string\n";
    }
