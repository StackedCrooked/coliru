
#include <map>
#include <iostream>

// Dummy types to use as parameters of constructor
struct A {};
struct B {};
struct C {};

class OnlyConstructible
{
    int m_i;

public:
	OnlyConstructible(int i, A a, B b, C c): m_i(i) { } // constructible

	int getI() const { return m_i; }

private:
	OnlyConstructible() = delete; // non default-constructible
	OnlyConstructible(const OnlyConstructible&) = delete; // non-copy-constructible
	OnlyConstructible& operator=(const OnlyConstructible&) = delete;  // non-copy-assignable
	OnlyConstructible(OnlyConstructible&&) = delete; // non-move-constructible
	OnlyConstructible& operator=(OnlyConstructible&&) = delete; // non-move-assignable
};


int main() {

	std::map<int, OnlyConstructible> myMap;

	A a; B b; C c;
	int i = 42;

	std::cout << "Before emplace. Size of map: " << myMap.size() << "\n";

	myMap.emplace(
		std::piecewise_construct,  // disambiguation hint
		std::forward_as_tuple(i),  // perfectly forward arguments to key_type constructor
		std::forward_as_tuple(13, a, b, c)); // perfectly forward arguments to value_type constructor

	std::cout << "After emplace. Size of map: " << myMap.size() << "\n";

	for (const auto& element : myMap)
	{
		std::cout << "\tKey: " << element.first << "\t\t, Value.getI(): " << element.second.getI() << "\n";
	}
		

}
