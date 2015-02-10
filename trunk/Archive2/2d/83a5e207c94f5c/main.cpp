#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <functional>

using namespace std;
//using namespace std::placeholders; 

struct Point { int x, y; };

class EnemyRhombus
{
public:
    int x,y;
    int dist(Point p)
    {
        int dx=abs(p.x-x);
        int dy=abs(p.y-y);
        return dx+dy-min(dx,dy);
    }
    bool points_cmp(Point f, Point s)
    {
        return dist(f)<dist(s);
    }
    void move()
    {
        vector<Point> candidates;
        //...
       // sort(candidates.begin(),candidates.end(),[&](Point f, Point s) { return dist(f) < dist(s) ;});
      /* std::sort( candidates.begin(),
           candidates.end(),
           bind(&EnemyRhombus::points_cmp, this, std::placeholders::_1, std::placeholders::_2));
        */   
           std::sort(candidates.begin(), candidates.end(), [this] (auto a, auto b) {
                    return points_cmp(a, b);
                    });
    }
};



int main() { cout << "It runs!"; }