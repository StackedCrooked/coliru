#include <iostream>
#include <functional>
#include <memory>

using namespace std;

function<int ()> makeLambda(unique_ptr<int> &&ptr) {
	return [ ptr( move(ptr) ) ] () {
		return *ptr;
	};
}

int main() {
    // Works
    {
    	unique_ptr<int> ptr( new int(10) );
        auto function1 = [ ptr(move(ptr)) ] {
            return *ptr;
        };
    }
    
    // Does not work
    {
        unique_ptr<int> ptr( new int(10) );
	    std::function<int ()> function2 = makeLambda( std::move(ptr) );
    }

	return 0;
}
