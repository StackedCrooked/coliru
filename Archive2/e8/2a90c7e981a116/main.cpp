#include <chrono>
#include <string>
#include <iostream>
#include <functional>
#include <vector>
#include <memory>


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
	cout << "Pushback Object: " << measure<>::execution([&]()
	{
		vector<MyObject> VectorOfObjects;
        VectorOfObjects.reserve(100000);
    
		for (int i = 0; i < 100000; i++) {
			VectorOfObjects.emplace_back("test");
		}
	}) << endl;


	cout << "Pushback Pointers: " << measure<>::execution([&]()
	{
		vector<unique_ptr<MyObject>> VectorOfPointers;
        VectorOfPointers.reserve(100000);
    
		for (int i = 0; i < 100000; i++) 
		    VectorOfPointers.emplace_back(new MyObject("test"));
	}) << endl;

	return 0;
}