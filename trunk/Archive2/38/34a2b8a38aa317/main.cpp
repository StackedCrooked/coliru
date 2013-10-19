yguguytytr65r7uohiuhuygugrfvhuirfiuhycgxhfhdfghfghfgdh#include <iostream>№#include <iostream>
#include <exception>

void function() throw(double) {
    throw 1.7;
}

void ex_hendler() {
	std::cout << "Unexpected exception" << std::endl;
	abort();
}

int main(int argc, char** argv) {
	std::set_terminate(ex_hendler);

	try {
		function();
	}
	catch(int a) {
		std::cout << "int exeption " << a << std::endl;
	}
	
	getchar();
	return 0;
}#include <iostream>
#include <exception>

void function() throw(double) {
    throw 1.7;
}

void ex_hendler() {
	std::cout << "Unexpected exception" << std::endl;
	abort();
}

int main(int argc, char** argv) {
	std::set_terminate(ex_hendler);

	try {
		function();
	}
	catch(int a) {
		std::cout << "int exeption " << a << std::endl;
	}
	
	getchar();
	return 0;
}#include <iostream>
#include <string>
#include <vector>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}


int main()
{
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
}
