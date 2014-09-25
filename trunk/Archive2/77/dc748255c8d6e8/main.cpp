#include <iostream>
#include <unordered_set>

template <class T1,class T2>
class MyPair
{
public:
    MyPair(const T1& a,const T2& b):
        first(a),
        second(b){}
    T1 first;
    T2 second;
};

template <typename T1, typename T2>
bool operator==(const MyPair<T1, T2>& P1, const MyPair<T1, T2>& P2)
{
    return P1.second==P2.second;
}

struct pair_hash {
    inline std::size_t operator()(const MyPair<int,int> & v) const {
        return std::hash<int>()(v.second);
    }
};
int main()
{

    std::unordered_multiset<MyPair<int,int>,pair_hash > a ({{0,1},{1,2}, {2,3},{3,4},{4,5},{5,7}});
    std::unordered_multiset<MyPair<int,int>,pair_hash > b({{0,2},{1,5}});

    for(const auto& pair : a){
        if(b.find(pair) == b.end()){
            std::cout<<"Index : "<<pair.first<<
                       " Value : "<<
                       pair.second<<'\n';
        }
    }
}
