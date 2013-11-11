#include <iostream>
#include <thread>
using namespace std;

void printHelloWorld() {
    for(int i = 0; i < 10; ++i)
     	cout << "Hello World\n" << flush;
}

int main() {
	thread t1(printHelloWorld);
	t1.join();
    cout << "\nJoined successfully";
}