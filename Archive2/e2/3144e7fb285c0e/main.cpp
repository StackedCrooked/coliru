#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    int a, b, c, d, e, f;
	
	std::thread([=] (int a, int b, int c) -> void {
		std::cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<"\n\n";
	}, a, b, c).join();
	
	
	auto lambda2 = [=](int a, int b, int c, int d, int e, int f) -> void {
		std::cout<<"a: "<<a<<" b: "<<b<<" c: "<<c<<" d: "<<" e: "<<e<<" f: "<<f;
	};
	
	std::thread(lambda2, a, b, c, d, e, f).join();
	
	std::this_thread::sleep_for(std::chrono::seconds(2));
	
	return 0;
}