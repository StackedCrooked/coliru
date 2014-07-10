#include <vector>
#include <iostream>

struct Vertex { 
  std::size_t id;
  Vertex(std::size_t const _id) : id(_id) {}
};

class Edge {
   Vertex& v1;
   Vertex& v2;
   double  cost;
public :
   Edge(Vertex& v_1, Vertex& v_2, double const _c) : v1(v_1), v2(v_2), cost(_c) {}
   Vertex& getv1() const { return v1; }
   Vertex& getv2() const { return v2; }
};

int main() {
    Vertex v1(1), v2(2);
    std::vector<Edge> alledges;
    alledges.push_back(Edge(v1, v2, 1.0));
    for(auto i : alledges) std::cout << i.getv1().id << "->" << i.getv2().id << std::endl;
    
    return 0;
}