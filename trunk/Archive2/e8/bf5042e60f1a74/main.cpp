#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

vector<int>& operator<<(vector<int>&, int);


std::vector<int>& operator>>(vector<int>& v, int& x);

vector<int>& operator<<(vector<int>& v, int x){    
	v.push_back(x);
	return v;
}

vector<int>& operator>>(vector<int>& v, int& x){

	if(v.empty()){
		throw std::runtime_error("The vector can't be empty!");	
	}
	x = v.back();
	v.pop_back();

	return v;

}

int main(int argc, char** argv) {
//Testing operator>>
    std::vector<int> test_right_stream;
	int out1, out2, out3;
	test_right_stream << 10;
	test_right_stream >> out1;
	if (10 == out1) {
		std::cout<<"Right stream works for single value!\n";
	}
	else {
		std::cout<<"Right stream fails for single value!\n";
	}
	//Should throw an exception
	try {
		test_right_stream >> out1;
		std::cout<<"Right stream didn't throw an exception when the vector was empty!\n";
	}
	catch (std::runtime_error) {
		std::cout<<"Right stream throws exception when vector is empty!\n";
	}
return 0;
}