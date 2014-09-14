#include <unordered_map>

typedef unsigned size_type;

struct internal_edge{
 size_type node1_uid;
 size_type node2_uid;
};

int main() {
    std::unordered_map<size_type, internal_edge> myMap;
    return 0;
} 
