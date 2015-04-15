#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>

class Module { };

struct Port {
    Module& owner;
    Port(Module& owner) : owner(owner) {}
};

struct InPort    : virtual Port    { using Port::Port; };
struct OutPort   : virtual Port    { using Port::Port; };
struct InOutPort : InPort, OutPort { using Port::Port; };

int main() {
    Module m;
    InOutPort iop(m);
}