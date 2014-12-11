#include <iostream>
#include <thread>
using namespace std;

void count()
{
    cout << "1!\n"
	     << "1!\n"
		 << "1!\n"
		 << "1!\n"
		 << "1!\n"
		 << "1!\n"
		 << "1!\n"
		 << "1!\n"
		 << "1!\n";
}

int main()
{
	thread test(count);
	cout << "0!\n"
	     << "0!\n"
		 << "0!\n"
		 << "0!\n"
		 << "0!\n"
		 << "0!\n"
		 << "0!\n"
		 << "0!\n"
		 << "0!\n";
    test.join();
	return 0;
}