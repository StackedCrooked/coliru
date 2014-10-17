#include <iostream>

#define WIDTH     10
#define HEIGHT    10

template<int a, int b>
constexpr int getArea() {
    const int area = a * b;
    static_assert(area < 1000, "Area is too big");
    return area; 
}

const int area = getArea<WIDTH, HEIGHT>();


int main(void) {
    
	std::cout << area;

	return 0;
}