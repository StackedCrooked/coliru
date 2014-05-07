#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;


vector<int>& operator<<(vector<int>& v, int x){    // Using vector<int>& because we are going to modify the vector in the parameter!
	v.push_back(x);	// Modifying vector v by adding integers to the back of it
	return v;	// Returning the modified vector!
}


vector<int>& operator>>(vector<int>& v, int& x){	// Using vector<int>& in declaration because we are modifying the returned vector from the parameter!
										// Using int& x because the integer x will also be modified

	if(v.empty()){	// You can't delete elements of a vector with no contents, silly!
		throw std::runtime_error("The vector can't be empty!");	
	}
	x = v.back();	// Integer x is modified, as promised, to the last element of vector v! 
	v.pop_back();	// Deleting the last element of vector v!

	return v;	// Returning vector v with the missing last element.

}


int main(){

	int score = 0;

	//Testing operator>>
	std::vector<int> test_right_stream;
	int out1, out2, out3;
	test_right_stream << 10;
	test_right_stream >> out1;
	if (10 == out1) {
		std::cout<<"Right stream works for single value! +10\n";
	  score += 10;
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
		std::cout<<"Right stream throws exception when vector is empty! +10\n";
	  score += 10;
	}

	test_right_stream << 20 << 30;
	test_right_stream >> out2 >> out3;
	if (20 == out3 and 30 == out2) {
		std::cout<<"Right stream works when called consecutively! +10\n";
	  score += 10;
	}
	else {
		std::cout<<"Right stream fails when called consecutively!\n";
	}
}