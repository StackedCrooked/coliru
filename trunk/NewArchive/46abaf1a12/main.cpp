#include <fstream>
#include <iostream>
#include <vector>

struct Point {
    int x;
    int y;
    int weight;
};

int main() {
    std::vector<Point> points;
    
    std::ifstream fin("test.txt");
    Point p;
    fin >> p.x >> p.y >> p.weight;
    
    points.push_back(p);
    
    std::cout << points.back().x << " " << points.back().y << " " << points.back().weight;
}