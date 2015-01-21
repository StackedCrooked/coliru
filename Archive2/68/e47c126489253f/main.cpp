#include <iostream>
#include <thread>
using namespace std;

int main() {
    std::thread t = std::thread([](void) -> void {std::cout<<"Hello\n";});
	// your code goes here
    t.join();
	return 0;
}