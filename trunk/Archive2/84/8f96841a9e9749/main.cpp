#include <iostream>
using namespace std;

template <typename T>
struct property {
    
	struct proxy {
		property * ptr;
		operator T () const { return ptr->get(); }
		auto operator=(T const & x) { ptr->set(x); return *this; }
	};
    
    proxy operator()() {
		return {this};
	}
	
	virtual void set(T const & x) = 0;
	virtual T get() const = 0;
	
protected:
	T value;
};

struct Foo {
	struct : property<int> {
		void set(int const & x){ value = x/2; }
		int get() const { return value * 2; }
	} even_int;
};

int main() {
	Foo f;
	f.even_int() = 5;
	cout << f.even_int() << endl;
	return 0;
}
