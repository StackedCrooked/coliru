#include <sstream>
#include <boost/archive/text_oarchive.hpp>

int main()
{
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss); 

    int m_recv_port = 42;
    oa & m_recv_port;

    const int number_of_objects = 0;
    oa & number_of_objects;
}
