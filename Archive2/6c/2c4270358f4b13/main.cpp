#include <iostream>
#include <functional>
#include <memory>

using namespace std;

function<int ()> makeLambda(unique_ptr<int> p) {
	return [ p( move(p) ) ] () {
		return *p;
	};
}

int main() {
	unique_ptr<int> ptr( new int(10) );
	auto function = makeLambda( std::move(ptr) );
	cout << function() << endl;
	return 0;
}
