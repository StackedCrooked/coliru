#include <iostream>
#include <string>
#include <vector>
#include <functional>

template<typename T>
struct generator_itterator{
    using ittr = generator_itterator<T>;
    T value;
    std::function<T(T&)> increment_function;
    
    bool operator!=(const ittr& rhs){
        return value != rhs.value;
    }
    
    ittr operator++(){
        value = increment_function(value);
        return *this;
    }
    
    T operator*(){ return value; }
};

template<typename T>
struct generator{
    T start, finish;
    std::function<T(T&)> increment_function;
    
    using ittr = generator_itterator<T>;
    
    ittr begin(){
        return ittr{start, increment_function};
    }
    
    ittr end(){
        return ittr{finish, increment_function};
    }
};

struct coord{
    int x, y, z;
    
    bool operator!=(const coord& rhs){
        return x != rhs.x || y != rhs.y || z != rhs.z;
    }
};

std::ostream& operator<<(std::ostream& os, const coord& c){
    return os << "(" << c.x << ", " << c.y << ", " << c.z << ")";
}

int main(){    
    auto start = coord{0,0,0};
    auto end = coord{1,1,1};
    auto g = generator<coord>{ start, end, [start, end](coord& v){
        if(v.x < end.x){
            v.x++;
        } else if (v.y <  end.y){
            v.x = start.x;
            v.y++;
        } else if (v.z < end.z){
            v.x = start.x;
            v.y = start.y;
            v.z++;
        }
        return v; // seems I *have* to return the new value...
    }};
    
    for(auto v : g){
        std::cout << v << std::endl;
    }
    std::cout << end << " :( canny 'generate' this" << std::endl;
}
