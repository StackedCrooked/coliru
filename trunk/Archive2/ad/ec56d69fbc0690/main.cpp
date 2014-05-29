#include <iostream>
#include <thread>
#include <string>
#include <vector>

using namespace std;

void Hello(string str) {  cout << "Hello" + str + "\n";  }

int main() {
    std::string str = {"World"};
	
    std::vector<std::thread> threads;

	threads.push_back(std::thread([&str](){ cout << "Hello" + str + "\n"; } ));
    threads.push_back(std::thread(Hello, str));

    for(auto& t : threads) {
       t.join();
    }
}