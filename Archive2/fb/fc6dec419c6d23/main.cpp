#include <sstream>
#include <iostream>

class oTraceStream : public std::ostringstream
{
public :

    oTraceStream(const int from, const unsigned int level)
    : m_from(from)
    , m_level(level)
    {
    }

    virtual ~oTraceStream(void)
    {
        std::cout << str();
    }

private :
    // unused for this sample
    int m_from;
    unsigned int m_level;
};


int main(int argc, char* argv[])
{
    oTraceStream(0,0) << "1st part " << " 2nd part" << std::endl;
    {
        oTraceStream tmp(0,0);
        tmp << "1st part " << " 2nd part" << std::endl;
    }

    return 0;
}