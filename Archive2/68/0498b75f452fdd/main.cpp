#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <memory>

class a {
public:
    void operator()(int){}
    void operator()(char){}
};

class b : public a {
public:
    void operator()(std::string){}
};

int main() {
    b x;
    x(1);
}