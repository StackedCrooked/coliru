#include<map>
#include<iostream>

struct Position {
    int a,b,c,d,e;
    Position():a(-1),b(-1),c(-1),d(-1),e(-1){}
    Position(int a,int b,int c,int d,int e):a(a),b(b),c(c),d(d),e(e)
    {}
};

int main() {
    std::multimap<int,Position> countries;
    int i = 4, j = 12;
    countries.emplace(std::piecewise_construct,
        std::forward_as_tuple(7),
        std::forward_as_tuple(i,j,-1,-1,-1));
    Position p = (*countries.begin()).second;
    std::cout 
        << p.a << ' '
        << p.b << ' '
        << p.c << ' '
        << p.d << ' '
        << p.e << ' ';
}
