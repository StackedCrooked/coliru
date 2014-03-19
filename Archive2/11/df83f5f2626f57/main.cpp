#include <map>
#include <functional>

struct A {
    void func1 (int) {};
	void func2 (int) {};
	void mapping() {
		// std::map<int, std::function<void(int)>> myMap = { {1, func1}, {2, func2} };
        
        using std::placeholders::_1 ;
        std::map< int, std::function<void(int)> > myMap = { { 1, std::bind( &A::func1, this, _1 ) }, 
                                                            { 2, std::bind( &A::func2, this, _1 ) } };
        
        std::map<int, std::function< void( A*, int )> > myMap2 = { { 1, &A::func1 }, { 2, &A::func2 } };
		// do whatever
        
        
	}
};

int main() {}