#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstring>

using namespace std;

struct A03
{
    A03(){
		common_init(42);
		message = NULL;
	}

	A03(std::string const& msg){
		common_init(42);
        throw std::bad_alloc();
		message = new char[msg.size()+1];
		strncpy(message,msg.c_str(),msg.size()+1);
	}

	~A03(){
		std::cout << "~A03" << std::endl;
		delete[] message;
	}

	int answer;

	char* message;

private:
	void common_init(int val){
		answer = val;
	}

	A03(A03 const&);
	A03& operator=(A03 const&);
};

int main()
{
	try{
		std::string any;
		A03 x(any);
		std::cout << "x.answer: " << x.answer << std::endl;
	}catch(std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}

