#include <string>

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