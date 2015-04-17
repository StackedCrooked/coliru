#include <iostream>
#include <string>
#include <cmath>
#include <array>

struct SomeStruct {
    struct x_getter {
		public:
			x_getter(SomeStruct *t)
				: thisPointer{t} {};

			// Getter
			operator float() const {
				return this->thisPointer->_x;
			};

		private:
			SomeStruct* thisPointer;
	};
	x_getter x{this};
    
    SomeStruct() : SomeStruct(0) {};
    SomeStruct(float x) : _x(x) {};
    
    SomeStruct(const SomeStruct& other) 
        : x(this), _x(std::move(other._x)) {};
    
    
    operator std::string() const {
		return std::string("(" + std::to_string(this->x) + ")");
	}

	friend std::ostream& operator << (std::ostream& stream, const SomeStruct &p) {
		return stream << std::string(p);
	};
    
    
    private:
        float _x;
};





struct PointWithExtraInfo {
    SomeStruct point;

	PointWithExtraInfo() {};
	PointWithExtraInfo(SomeStruct p) : point{p} {};
	PointWithExtraInfo(float x, float y) {
		this->point = SomeStruct(x);
	};

	operator SomeStruct() { 
		return this->point;
	};
};


// There needs to be this level of indirection to get the weird memory stuff
SomeStruct PointOnLine(SomeStruct p0, SomeStruct p1) {
	return SomeStruct(
		1337.12345
	);
}
PointWithExtraInfo PointOnEllipticalArc(SomeStruct p0, SomeStruct p1, float t) {
    return PointOnLine(p0, p1);
}


// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
  
    std::cout << "asdf" << std::endl;
    
    SomeStruct foo = PointOnEllipticalArc({0.5678}, {10.1234}, 0.5);
    std::cout << foo << std::endl;
    
    SomeStruct bar = PointOnEllipticalArc({5.45}, {6.12}, 0.5);
    std::cout << bar << std::endl;
    
    std::cout << "----------" << std::endl;






	return 0;
}



