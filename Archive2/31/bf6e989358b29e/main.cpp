#include <iostream>    	// std::cout, std::endl
#include <vector> 		// std::vector
#include <algorithm> 	// std::min_element
#include <utility> 		// std::begin, std::end

using namespace std;

int main() {
	using arithmetic = int; // whatever arithmetic type you want
	vector<arithmetic> data = { 105, 2, -30, 44, 0, -3 };
	
	auto result = min_element(begin(data), end(data));
	if (result != end(data)) {
		cout << "min_element=" << *result << endl;
	} else {
		cout << "data appears to be empty (unexpected)" << endl;
	}
}