struct Point {
    Point& operator=( Point const & ) & = default;
    Point& operator=( Point const & ) && = delete;
    friend Point operator+( Point const & a, Point const & b ) { return { a + b }; }
    int member = 0;
};
int main() {
    Point a,b;
    a = b;
    a+b = a;
}
