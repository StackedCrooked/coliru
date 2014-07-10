#include <iostream>
#include <vector>

struct Vertex { };

class Edge {
   Vertex& v1;
   Vertex& v2;
   double  cost;
public :
   Edge(Vertex& v_1, Vertex& v_2, double const _c) : v1(v_1), v2(v_2), cost(_c) { }
};

int main() {
    Vertex v1, v2, v3;
    std::vector<Edge> v {Edge(v1, v2, 1.0), Edge(v2, v3, 2.0), Edge(v3, v1, 5.0)};
    return 0;
}