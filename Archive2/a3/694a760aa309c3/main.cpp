#include <iostream>
#include <set>

struct VertexTypePos3Normal {
    friend bool operator<(const VertexTypePos3Normal&, const VertexTypePos3Normal&);
};

bool operator<(const VertexTypePos3Normal&, const VertexTypePos3Normal&) {
    return true; 
}

int main() {
    std::set<VertexTypePos3Normal> set;
}