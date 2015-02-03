#include <string>
#include <iostream>

#include <boost/type_index.hpp>

class CRoom
{
public:
    CRoom(std::string) {};
} room("test");

int main()
{
    std::cout << boost::typeindex::type_id_with_cvr<decltype(room)>().pretty_name() << '\n';
}
