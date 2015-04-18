#include <iostream>
#include <string>
#include <cmath>


template <typename Tx = float, typename Ty = Tx>
struct PointGeneric {
	
	struct x_getter {
		public:
			x_getter(PointGeneric *t)
				: thisPointer{t} {};

			// Getter
			operator Tx() const {
				return this->thisPointer->_x;
			};

		private:
			PointGeneric<Tx, Ty>* thisPointer;
	};
	x_getter x{this};

	struct y_getter {
		public:
			y_getter(PointGeneric *t)
				: thisPointer{t} {};

			// Getter
			operator Ty() const {
				return this->thisPointer->_y;
			};

		private:
			PointGeneric<Tx, Ty>* thisPointer;
	};
	y_getter y{this};



	PointGeneric() 
		: PointGeneric { 0, 0 } {};

	PointGeneric(Tx x, Ty y)
		: _x{x}, _y{y} {};

	// Copy Constructor
	PointGeneric(const PointGeneric<Tx, Ty>& other) 
		: x(this), y(this), _x(std::move(other._x)), _y(std::move(other._y)) {};


	bool equalsWithinTolerance(PointGeneric<Tx, Ty> other) {
		return equalsWithinTolerance(other, 0.0001f);
	};

	bool equalsWithinTolerance(PointGeneric<Tx, Ty> other, float tolerance) {
		return fabs(this->x - other.x) <= tolerance && fabs(this->y - other.y) <= tolerance;
	};

	// equality operators
	bool operator == (const PointGeneric<Tx, Ty> &v) { return (this->x == v.x) && (this->y == v.y); }
	bool operator != (const PointGeneric<Tx, Ty> &v) { return !this->operator==(v); }

	
	operator std::string() const {
		return std::string("(" + std::to_string(this->x) + ", " +  std::to_string(this->y) + ")");
	}

	friend std::ostream& operator << (std::ostream& stream, const PointGeneric<Tx, Ty> &p) {
		return stream << std::string(p);
	};


	private:
		Tx _x;
		Ty _y;
};

// auto myPt1 = Point(5, 6);
// std::cout << myPt1 << std::endl;
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx&& x, Ty&& y) {
	return { std::forward<Tx>(x), std::forward<Ty>(y) };
};
/* * /
// float someNum = 5;
//auto myPt2 = Point(someNum, someNum);
// std::cout << myPt2 << std::endl;
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx& x, Ty& y) {
	return { x, y };
};
// auto myPt3 = Point(someNum, 6);
// std::cout << myPt3 << std::endl;
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx& x, Ty&& y) {
	return { x, std::forward<Ty>(y) };
};
// auto myPt4 = Point(6, someNum);
// std::cout << myPt4 << std::endl;
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx&& x, Ty& y) {
	return { std::forward<Tx>(x), y };
};
// auto fooPt5 = Point(5, 6);
// auto myPt5 = Point(fooPt5);
template <typename T>
static T Point(T&& p) {
	return { std::forward<T>(p) };
};
// Convert between generic point types. ex. double->float
// auto fooPt6 = Point(5.123456789, 6.987654321);
// auto myPt6 = Point<float>(fooPt6);
template <typename TargetType, typename T>
static PointGeneric<TargetType, TargetType> Point(T&& p) {
	return { std::forward<TargetType>(TargetType(p.x)), std::forward<TargetType>(TargetType(p.y)) };
};
/* */



// Just testing out passing in some stuff
PointGeneric<> foobar(float x, float y) {
	return Point(x, y);
};

// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
  
    std::cout << "asdf" << std::endl;
    
    //auto asdf = Point(static_cast<PointGeneric<>>(Point(1.23456, 2.34567));
    //auto foo = Point(1.23456, 2.34567); auto bar = Point(float(foo.x), float(foo.y));
    //auto foo = Point(1.23456, 2.34567); auto bar = Point(static_cast<float>(foo.x), static_cast<float>(foo.y));
    
    /* */
    auto myPt1 = Point(5, 6);
    std::cout << myPt1 << std::endl;
    /* */
    
    std::cout << "----------" << std::endl;
    
    /* */
    float someNum = 5;
    auto myPt2 = Point(someNum, someNum);
    std::cout << myPt2 << std::endl;
    someNum = 8;
    std::cout << myPt2 << std::endl;
    /* */
    
    std::cout << "----------" << std::endl;
    
    /* */
    auto myPt3 = Point(someNum, 6);
    std::cout << myPt3 << std::endl;
    auto myPt4 = Point(6, someNum);
    std::cout << myPt4 << std::endl;
    /* */
    
    
    std::cout << "----------" << std::endl;



    /* */
    std::cout << foobar(4, 5) << std::endl;
    /* */
    



	return 0;
}



