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
        
    //PointGeneric(Tx& x, Ty& y) : _x{x}, _y{y} {};

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

	
	#if defined(ARDUINO)
		operator String() {
			return String("(" + SVGCurveLib::FloatToString((float)this->x, 4) + ", " +  SVGCurveLib::FloatToString((float)this->y, 4) + ")");
		}
	#else
		operator std::string() const {
			return std::string("(" + std::to_string(this->x) + ", " +  std::to_string(this->y) + ")");
		}

		friend std::ostream& operator << (std::ostream& stream, const PointGeneric<Tx, Ty> &p) {
			return stream << std::string(p);
		};
	#endif


	private:
		Tx _x;
		Ty _y;
};

template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx&& x, Ty&& y) {
	return { std::forward<Tx>(x), std::forward<Ty>(y) };
};
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx& x, Ty& y) {
	return { x, y };
};
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx& x, Ty&& y) {
    return { x, std::forward<Ty>(y) };
};
template <typename Tx = float, typename Ty = Tx>
static PointGeneric<Tx, Ty> Point(Tx&& x, Ty& y) {
    return { std::forward<Tx>(x), y };
};
template <typename T>
static T Point(T&& p) {
	return { std::forward<T>(p) };
};




// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
  
    std::cout << "asdf" << std::endl;
    
    /* */
    auto myPt1 = Point(5, 6);
    std::cout << myPt1 << std::endl;
    /* */
    
    /* */
    float someNum = 5;
    auto myPt2 = Point(someNum, someNum);
    std::cout << myPt2 << std::endl;
    someNum = 8;
    std::cout << myPt2 << std::endl;
    /* */
    
    
    /* */
    auto myPt3 = Point(someNum, 6);
    std::cout << myPt3 << std::endl;
    auto myPt4 = Point(6, someNum);
    std::cout << myPt4 << std::endl;
    /* */
    
    
    std::cout << "----------" << std::endl;






	return 0;
}



