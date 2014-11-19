#include <iostream>
using namespace std;

using A = struct { 
    auto _x() {
		auto p = this; 
		
		struct B { 
			using this_type = decltype(p); 
		};
		
		return B{}; 
	}
	
	using this_type = decltype(A{}._x())::this_type;
};

int main() {
	// your code goes here
	return 0;
}