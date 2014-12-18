#include <iostream>
#include <cmath>
#include <thread>
#include <future>
#include <functional>
#include <vector>
#include <stdint.h>
#include <iostream>
#include <sstream>
class Foo{
private:
int i = 6;
public:

 friend std::ostream& operator<< (std::ostream& stream, const Foo& x);

};


std::ostream& operator<<(std::ostream& stream, const Foo& x)
{
    stream << x.i;

    return stream;
}

int main()
{
    Foo f;
    std::stringstream ss;
    ss << f;
    std::cout << ss.str();
}