#include <map>
#include <iostream>

struct foo{
    int x, y, z;
};

bool operator< (const foo& lhs, const foo& rhs){
    return lhs.x < rhs.x || lhs.y < rhs.y || lhs.z < rhs.z;
}

int main(){
    foo a{1,1,5};
    foo b{1,1,0};
    foo c{1,1,-5};
    if(b < a){
        std::cout << "b < a" << std::endl;
    }
    if(c < b){
        std::cout << "c < b" << std::endl;
    }
    
    std::map<foo, int> bar{
        { {1,1,5}, 6 },
        { {1,1,0}, 6 },
        { {1,1,-5}, 6 }
    };
    
    std::cout << "size: " << bar.size() << std::endl;    
    bar.erase(a);
    std::cout << "size: " << bar.size() << std::endl;
    bar.erase(b);
    std::cout << "size: " << bar.size() << std::endl;
    bar.erase(c);
    std::cout << "size: " << bar.size() << std::endl;
}