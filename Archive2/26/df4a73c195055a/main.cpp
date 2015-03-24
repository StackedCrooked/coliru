#include <iostream>
#include <typeinfo>
#include <iomanip>
#include <sstream>

template <class T>
void show_size(T t) { 
    std::cout << std::setw(15) <<  typeid(T).name() << " => " << sizeof(t) << "bytes\n";
}

template <class T, typename ...Args>
void show_size(T t, Args...args) { 
	show_size(t);
	show_size(args...);
}

int main() { 
	typedef long double ld;

	show_size(char(), short(), int(), long(), float(), double(), ld());
}
