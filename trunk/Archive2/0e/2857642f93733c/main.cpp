#include <iostream>

class Vector2
{
    public:
		static Vector2 invalid;

		Vector2(bool isValid);
		Vector2(const Vector2& vec);
};

Vector2 Vector2::invalid(false);

Vector2::Vector2(bool isValid)
{
    std::cout << "isValid in contructor" << isValid << std::boolalpha << std::endl;
	
}

Vector2::Vector2(const Vector2& vec)
{
	std::cout << "asdf" << std::boolalpha << std::endl;
}

int main()
{
    Vector2(false);
}
