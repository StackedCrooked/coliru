#include <chrono>
#include <string>
#include <iostream>
#include <functional>
#include <vector>


using namespace std;


// 1. A way to easily measure elapsed time -------------------
template<typename TimeT = std::chrono::milliseconds>
struct measure
{
    template<typename F>
	static typename TimeT::rep execution(F const &func)
	{
		auto start = std::chrono::system_clock::now();
		func();
		auto duration = std::chrono::duration_cast< TimeT>(
			std::chrono::system_clock::now() - start);
		return duration.count();
	}
};
// -----------------------------------------------------------


// 2. MyObject -----------------------------------------------
struct MyObject {
	string mem;
	MyObject(const char *text) : mem(text) {};
};
// -----------------------------------------------------------


int main() 
{
	vector<MyObject> VectorOfObjects;
	vector<MyObject *> VectorOfPointers;
	
	cout << "Pushback Object: " << measure<>::execution([&]()
	{
		for (int i = 0; i < 100000; i++) {
			MyObject x("test");
			VectorOfObjects.push_back(x);
		}
	}) << endl;


	cout << "Pushback Pointers: " << measure<>::execution([&]()
	{
		for (int i = 0; i < 100000; i++) VectorOfPointers.push_back(new MyObject("test"));
		for (auto &item : VectorOfPointers) delete item;
	}) << endl;

	return 0;
}