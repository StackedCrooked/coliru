#include <iostream>

    typedef int Point;
 
    class Data {
    public:
        Data(Point a, Point b, Point c): _one(a), _two(b), _three(c) {}

        template <typename F>
        void apply(F&& f) {
            f(_one);
            f(_two);
            f(_three);
        }

    private:
        Point _one; 
        Point _two;
        Point _three;
    }; // class Data
    
    int main() {
        Data d(1, 2, 3);
        
        d.apply([](Point& p) { ++p; });
        
        d.apply([](Point const& p) { std::cout << p << "\n"; });
    }
    
    
    