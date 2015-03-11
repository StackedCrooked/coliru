#include <iostream>

namespace coliru {

namespace def_enum {

enum ShockObject {
    Undefined = 0,
	None = 1,
	Spot = 2,
	Volatility = 3,
	Forex = 4,
	Yield = 5,
	DivAmount = 6,
	Repos = 7,
	Forward = 8,
	IVSkew = 9
};

} // def_enum

typedef def_enum::ShockObject ShockObject;

} // coliru

int main()
{
    // C# style enum namespace enclosing
    coliru::ShockObject so = coliru::ShockObject::Forex;
    
    std::cout << so << std::endl;
}

int main2()
{
    // Does not pollute the outer scope
    using namespace coliru;
    
    std::cout << Forex << std::endl;
}
