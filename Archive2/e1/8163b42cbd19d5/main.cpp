#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

std::istream& readline(std::istream& is, std::string& t)
{
    t.clear();

    // The characters in the stream are read one-by-one using a std::streambuf.
    // That is faster than reading them one-by-one using the std::istream.
    // Code that uses streambuf this way must be guarded by a sentry object.
    // The sentry object performs various tasks,
    // such as thread synchronization and updating the stream state.

    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for(;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}




int main()
{
    // intentionally non-compliant: uses LF in one place where CRLF is expected
    std::string reqdata = "GET /index.html HTTP/1.1\r\nHost: localhost:8081\r\nConnection: keep-alive\r\nContent-Length: 3\r\n\r\nABC";
    
    std::istringstream iss(reqdata);
    std::string line;
    readline(iss, line);
    std::cout << "Initial request line: " << line;
    
    if (!iss)
    {
        return 1;
    }
    
    while (readline(iss, line))
    {
        if (line.empty())
        {
            break;
        }
        std::cout << "Header: " << line << std::endl;
    } 
    
    
    std::string str;
    str.resize(1024);
    iss.read(&str[0], str.size());
    std::cout << "Payload: " << str << std::endl;
    
    
}