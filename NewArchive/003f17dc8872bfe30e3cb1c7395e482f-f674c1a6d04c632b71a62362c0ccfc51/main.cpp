#ifndef TYPENAME_HPP_
#define TYPENAME_HPP_ 1

#include <typeinfo>
#include <type_traits>
#include <string>
#include <cxxabi.h>

template<typename FIRST> std::string typeName() {

    std::string tName;

	// get name of the type (and remove the '\n' at the end)
	int status; char* name = abi::__cxa_demangle(typeid(FIRST).name(), nullptr, nullptr, &status);
	if (name != nullptr) { tName += name; }
	free(name);

	// check whether we have a const qualifier
	if(std::is_const<FIRST>::value) { tName += " const"; }

	// check whether type declares a volatile variable
	if(std::is_volatile<FIRST>::value) { tName += " volatile"; }

	// check for lvalue and rvalue references
	if(std::is_lvalue_reference<FIRST>::value) { tName += "&"; }
	if(std::is_rvalue_reference<FIRST>::value) { tName += "&&"; }

	return tName;
}

template<typename FIRST, typename SECOND, typename... OTHER> std::string typeName() {
	return typeName<FIRST>() + ", " + typeName<SECOND, OTHER...>();
}

#endif /* TYPENAME_HPP_ */

#include <iostream>


struct object {

    object() { std::cout << "# created" << std::endl; }
	~object() { std::cout << "# destroyed" << std::endl; }
	
	object(const object&) { std::cout << "# copied 2" << std::endl; }
	object(object&&) { std::cout << "# moved" << std::endl; }

	void talk(const char* text) const { std::cout << "# talk " << text << std::endl; }
};


void makeItTalk(object& obj) { obj.talk("a"); }
void makeItTalk(object&& obj) { obj.talk("b"); }
void makeItTalk(const object& obj) { obj.talk("c"); }
void makeItTalk(const object&& obj) { obj.talk("d"); }


template<typename ...Pars> struct g {

	static void h(Pars&&... pars) {
 		std::cout << typeName<Pars...>() << std::endl;
 		makeItTalk(std::forward<Pars>(pars)...);
	}

};


template<typename ... Pars> void f(Pars&& ... pars) { 
	std::cout << typeName<Pars...>() << std::endl;
	g<Pars...>::h(std::forward<Pars>(pars)...);
}


int main() {

	{
		object obj1;
		f(obj1);
	}
	
	std::cout << std::endl;
	
	{
		object obj2;
		f(std::move(obj2));
	}
	
	std::cout << std::endl;
	
	{
		const object obj3;
		f(obj3);
	}
	
	std::cout << std::endl;
	
	{
		const object obj4;
		f(std::move(obj4));
	}
	
	return 0;
}

// compile by
// g++ -std=gnu++0x -o test test.cpp
