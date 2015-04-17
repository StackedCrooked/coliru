#include <iostream>
#include <string>


template <typename Tx = float, typename Ty = float>
struct Point_type {
    Tx x;
    Ty y;
    
    Point_type() : Point_type{0, 0} {};
    Point_type(Tx x, Ty y) : x{x}, y{y} {};
    
    operator std::string() {
        return std::string("(" + std::to_string(this->x) + ", " +  std::to_string(this->y) + ")");
    };
    
    friend std::ostream& operator << (std::ostream& stream, const Point_type &p) {
		return stream << (std::string)(Point_type)p;
	};
};

template <typename Tx, typename Ty>
Point_type<Tx, Ty> Point(Tx&& x, Ty&& y) {
	return { std::forward<Tx>(x), std::forward<Ty>(y) };
};

template <typename T>
T Point(T&& p) {
    return { std::forward<T>(p) };
};


/* */
// Just a class that wants to store those points
struct PointCloud {
    // It wants some generic here :(
    Point_type<> start;
    Point_type<> end;
};
/* */


// Standard C/C++ main entry point
int main (int argc, char * const argv[]) {
    std::cout << Point(3, 4) << std::endl;
    std::cout << Point(5.123456789f, 6.123456789f) << std::endl;
    std::cout << Point(5.123456789, 6.123456789) << std::endl;
    
    auto myPt1 = Point(5.123456789, 6.123456789);
    std::cout << Point(myPt1) << std::endl;

	return 0;
}



