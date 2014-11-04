#include <boost/phoenix.hpp>
#include <unordered_map>
#include <functional>

enum Opcode {
    OpFoo,
    OpBar,
    OpQux,
};

namespace std
{
    template<> struct hash<Opcode> : std::hash<int>{};
}


// this should be a pure virtual ("abstract") base class
class Operation {
    // ...
};

class OperationFoo: public Operation {
    // this should be a non-abstract derived class
};

class OperationBar: public Operation {
    // this should be a non-abstract derived class too
};

std::unordered_map<Opcode, std::function<Operation*()>> factory {
    { OpFoo, boost::phoenix::new_<OperationFoo>() },
    { OpBar, boost::phoenix::new_<OperationBar>() },
    //{ OpQux, []() { return new OperationQux; } },
};

int main() {
	Opcode opc = OpFoo;
	Operation *objectOfDynamicClass = factory[opc]();
    
    delete objectOfDynamicClass;
}