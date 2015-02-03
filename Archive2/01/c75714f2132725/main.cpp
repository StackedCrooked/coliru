#include <string>
#include <iostream>

class CRoom
{
public:
    CRoom(std::string) {};
} room("test");

template<typename T>
struct dump;

int main()
{
    dump<decltype(room)> d;
}
