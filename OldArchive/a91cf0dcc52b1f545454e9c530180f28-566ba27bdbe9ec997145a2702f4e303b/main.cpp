#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstring>

using namespace std;

struct A11
{
    A11(int ans) : answer(ans) {}

	A11() : A11(42){
		message = nullptr;
	}

	A11(std::string const& msg) : A11(42){
        throw std::bad_alloc();
		message = new char[msg.size()+1];
		strncpy(message,msg.c_str(),msg.size()+1);
	}

	~A11(){
		std::cout << "~A11" << std::endl;
		delete[] message;
	}

	int answer;

	char* message;

private:
	A11(A11&&)=delete;
	A11(A11 const&)=delete;
	A11& operator=(A11&&)=delete;
	A11& operator=(A11 const&)=delete;
};

int main()
{
	try{
		std::string any;
		A11 x(any);
		std::cout << "x.answer: " << x.answer << std::endl;
	}catch(std::exception& e){
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}

