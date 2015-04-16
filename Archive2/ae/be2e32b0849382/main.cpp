//
// portable 4 character codes
//

template<int N>
struct int_{};

struct FourCC
{
	template<int N>
	constexpr FourCC(char const (&_fourCC)[N])
		: value(MakeValue(_fourCC, int_<N-1>()))
	{
		static_assert(N <= 5, "4 character code must contain at most 4 characters"); // plus null-terminator
	}
    
    constexpr operator unsigned() const { return value; }

	unsigned value;
    
private:
    template<int N>
    static constexpr unsigned MakeValue(char const (&_fourCC)[N], int_<1>)
    {
        return _fourCC[0];
    }

    template<int N, int I>
    static constexpr unsigned MakeValue(char const (&_fourCC)[N], int_<I>)
    {
        return (MakeValue(_fourCC, int_<I-1>()) << 8) | _fourCC[I-1];
    }
};

#include <iostream>

int main()
{
    constexpr FourCC fcc("flck");
    //static_assert(fcc.value == 'flck', "...");
    std::cout << std::hex << 'flck' << "\n";
    
    switch (fcc)
    {
    case FourCC("flck"):
        std::cout << fcc.value << "\n";
        break;
    }
}