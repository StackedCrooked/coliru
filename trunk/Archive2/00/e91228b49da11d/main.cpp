//
// portable 4 character codes
//

struct FourCC
{
	template<int N>
	constexpr FourCC(char const (&_fourCC)[N])
		: value((_fourCC[0] << 24) | (_fourCC[1] << 16) | (_fourCC[2] << 8) | _fourCC[3])
	{
		static_assert(N <= 5, "4 character code must contain at most 4 characters"); // plus null-terminator
	}
    
    constexpr operator int() const { return value; }

	int value;
};

#include <iostream>

int main()
{
    constexpr FourCC fcc("flck");
    //static_assert(fcc.value == 'flck', "...");
    
    switch (fcc)
    {
    case FourCC("flck"):
        std::cout << fcc.value << "\n";
        break;
    }
}