#include <iostream>

struct Vertex
{
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& out, const Vertex& v)
{
    out << "{ " << v.x << ", " << v.y << " }"; 
    return out;
}

int main()
{
    Vertex v = Vertex{1, 2};
    Vertex* q = &v;
    Vertex t = *q;
    q->x = 4;
    std::cout << "*q: " << *q << "\n";
    std::cout << " t: " << t << "\n";
}
