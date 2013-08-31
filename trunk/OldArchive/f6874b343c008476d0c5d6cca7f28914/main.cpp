//C++ Faces, by Serge Azel
#include <iostream>


struct O_O
{
    O_O() {}

	O_O(const O_O& in) {}

	O_O(bool in) {};


	operator bool()
	{
		return true;
	}
} _;


O_O& operator-(O_O& face, O_O& other)
{
	return face;
}


O_O& operator*(O_O& face, O_O& other)
{
	return face;
}


O_O& operator+(O_O& face, O_O& other)
{
	return face;
}


O_O& operator<(O_O& face, O_O& other)
{
	return face;
}


O_O& operator>(O_O& face, O_O& other)
{
	return face;
}


O_O& operator^(O_O& face, O_O& other)
{
	return face;
}


template <typename T>
O_O& operator-(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator*(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator+(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator<(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator>(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator^(O_O& face, const T& other)
{
	return face;
}


template <typename T>
O_O& operator-(O_O& face)
{
	return face;
}


template <typename T>
O_O& operator+(O_O& face)
{
	return face;
}


template <typename T>
O_O& operator-(const T& other, O_O& face)
{
	return face;
}


template <typename T>
O_O& operator*(const T& other, O_O& face)
{
	return face;
}


template <typename T>
O_O& operator+(const T& other, O_O& face)
{
	return face;
}


template <typename T>
O_O& operator<(const T& other, O_O& face)
{
	return face;
}


template <typename T>
O_O& operator>(const T& other, O_O& face)
{
	return face;
}


template <typename T>
O_O& operator^(const T& other, O_O& face)
{
	return face;
}


// main.cpp


int main()
{
    int girl, wat_r_u_doing, staahp, herp, derp, why, wub, woo;


	O_O v_v;

	girl >_> wat_r_u_doing? 
	girl: -_- staahp,

	herp <_> derp,

	why ^_^ wub ^_^ woo <3;
    
    std::cout << "It compiles.\n\n";
    
}