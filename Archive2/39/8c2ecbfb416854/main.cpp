#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Vertex {
    public:
     int i;
};

bool greaterThan(Vertex * v1, Vertex *v2){

    return v1->i > v2->i;
}

int main()
{
    std::vector<Vertex*> v;
    v.push_back(new Vertex { 5 });
    v.push_back(new Vertex { 1 });
    v.push_back(new Vertex { 3 });
    v.push_back(new Vertex { 6 });
    v.push_back(new Vertex { 2 });
    
    std::sort(v.begin(), v.end(), &greaterThan);
    
    for(auto& ve : v)
       std::cout << ve->i << " ";
}
