#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point{
        int x,y;//Integer coordinates for simplicity
public:
        Point();
        Point(int, int);

        double get_Y() const {return y;}

        void Print();
};

Point::Point(){//Initialize blank Points to blank values (zero)
        x = 0;
        y = 0;
}

Point::Point(int a, int b){
        x = a;
        y = b;
}

void Point::Print(){
        cout<< "Point: (" << x << "," << y << ")" << '\t';

}
//comparison function for comparing Point class objects
struct Compare_Y{
        bool operator()(const Point& p1, const Point& p2)
                { return p1.get_Y() > p2.get_Y(); }
};

int main(){

        //Store 10 Points in any container, initialize, and print each Point
        vector<Point> v;

        for(int i = 0; i < 10; ++i){
        v.push_back(Point(i*5,i*10));
        }

        for(int i = 0; i < 10; ++i){
        v[i].Print();
        }

        //Write function to find Point with maximum y coordinate by any STL Algorithm (See C++ site w/ them)
        //Return the point with the max y coord. Return the x AND y here.

        Compare_Y c;
        cout << "The Point with the largest Y value is " << *max_element(v.begin(),v.end(),c);

return 0;

}