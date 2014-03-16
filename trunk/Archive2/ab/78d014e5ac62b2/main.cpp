#include <iostream>
#include <functional>
#include <utility>
#include <iomanip>
#include <vector>
#include <atomic>
#include <thread>


std::string unmangle(std::string name);

template<typename T>
std::string name_type(){
    auto name = unmangle(typeid(T).name());

    if(std::is_const<T>::value) name += " const";
	if(std::is_volatile<T>::value) name += " volatile";

	if(std::is_reference<T>::value) name += "&";
	else if(std::is_pointer<T>::value) name += "*";

	return name;
}

#include <cxxabi.h>

std::string unmangle(std::string name){
	int status;
	size_t len;
	auto ptr = __cxxabiv1::__cxa_demangle(name.c_str(),nullptr,&len,&status);
	if(status != 0) throw status;
	std::string ret(ptr);
	::free(ptr);
	return ret;
}

using namespace std;

#define DBG(x) { cout << left << setw(40) << setfill(' ') << #x << (x) << endl; }


template<typename>
struct deduce_class{};

template <typename Ret, typename Class, typename... Args>
struct deduce_class<Ret (Class::*)(Args...) const noexcept>
{
	typedef Class type;
};

struct Test
{
	void f(){}
};

auto main() -> int
{
	auto ptr = &string::size;

	typename deduce_class<decltype(ptr)>::type x;

	cout << name_type<decltype(x)>() << endl;
	return 0;
}

