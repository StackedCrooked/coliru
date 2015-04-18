#include <iostream>
#include <string>
#include <cmath>


template <typename Tx = float>
struct SomethingGeneric {
    
    SomethingGeneric(Tx x) : _x(x) {};
    // Copy Constructor
	SomethingGeneric(const SomethingGeneric<Tx>& other) : _x(std::move(other._x)) {};
    
    
    Tx getX() const {
        return this->_x;
    };
    
    operator std::string() const {
		return std::string("(" + std::to_string(this->_x) + ")");
	}

	friend std::ostream& operator << (std::ostream& stream, const SomethingGeneric<Tx> &p) {
		return stream << std::string(p);
	};
    
    private:
        Tx _x;
};


template <typename Tx = float>
static SomethingGeneric<std::decay_t<Tx>> Something(Tx&& x) {
	return { std::forward<Tx>(x) };
};


// Just testing out passing in some stuff
SomethingGeneric<> foobar(float x) {
    return Something(x);
};


// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
    std::cout << foobar(5) << std::endl;
   
	return 0;
}



