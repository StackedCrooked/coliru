#include <iostream>
#include <thread>
#include <string>

using namespace std;

void Hello(string str) {  cout << "Hello" + str + "\n";  }

int main() {
    std::string str = {"World"};
	
	std::thread t1([&str](){ cout << "Hello" + str + "\n"; } );
    std::thread t2(Hello, str);
    t1.join();
    t2.join(); 

	return 0;
}