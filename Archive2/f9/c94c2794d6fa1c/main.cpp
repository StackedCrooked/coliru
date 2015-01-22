#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

template <typename T1,typename T2> class MemberCmp {
public:
    explicit MemberCmp( T1 T2::* t) : memPointer(t) {}
    
    bool operator() (const T2 &lhs, const T2 &rhs) const {
        return lhs.*(memPointer) < rhs.*(memPointer);
    }
    
    T1 T2::* memPointer;
};

template <typename T, typename V>
MemberCmp<V, T> by_member(V T::* mem_ptr) {
    return MemberCmp<V, T>(mem_ptr);
}

struct ABC{
    double x;
    double y;
};

int main() {
    std::vector<ABC> vec;
    
    ABC ab;
    ab.x = 9;
    ab.y = 89;
    vec.push_back(ab);
    
    ab.x = 10;
    ab.y = 10;
    vec.push_back(ab);
    
    ab.x = 5;
    ab.y = 100;
    vec.push_back(ab);
    
    
    std::sort(vec.begin(),  vec.end(), by_member(&ABC::x));

    std::vector<ABC>::const_iterator itr = vec.begin();
    for (itr = vec.begin(); itr != vec.end(); ++itr)
        std::cout << itr->x <<std::endl;

    std::cout <<"——————–"<<std::endl;
    
    std::sort(vec.begin(),  vec.end(),  by_member(&ABC::y));
    for (itr = vec.begin(); itr != vec.end(); ++itr)
        std::cout << itr->y <<std::endl;
    return 0;
}