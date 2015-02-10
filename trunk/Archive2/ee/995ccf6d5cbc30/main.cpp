#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

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
    
    void move()
    {
        vector<Point> candidates;
        //...
        sort(candidates.begin(),candidates.end(),[&](Point f, Point s) { return dist(f) < dist(s) ;});
    }
};



int main() { cout << "It runs!"; }