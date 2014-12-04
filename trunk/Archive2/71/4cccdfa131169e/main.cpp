#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

class Serializable
{
};

class MyData : public Serializable
{
};


void GetData(Serializable& data)
{
}

template<typename T>
void GetData(T& data)
{
    std::istringstream s{"test"};
    s >> data;
}

int main()
{
    MyData d;
    GetData(d);
}