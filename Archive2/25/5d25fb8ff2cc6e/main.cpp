#include <cstdio>
#include <algorithm>

struct OnlyMovable {
    OnlyMovable() {puts("ctor");}
    OnlyMovable(const OnlyMovable&) = delete;
    OnlyMovable& operator= (const OnlyMovable&) = delete;
    
    OnlyMovable(OnlyMovable&& rhs) {puts("moving ctor");}
    OnlyMovable& operator= (OnlyMovable&& rhs) {puts("moving ass op"); return *this;}
    
    ~OnlyMovable() {puts("dtor");}
};

OnlyMovable getOnlyMovable() {
    return OnlyMovable();
}

int main() {
    {
        OnlyMovable om;
    }
    puts("=====");
    {
        OnlyMovable om = OnlyMovable();
    }
    puts("=====");
    {
        OnlyMovable om = getOnlyMovable(); 
    }
    puts("=====");
    {
        OnlyMovable om1;
        OnlyMovable om2;
        om1 = std::move(om2);
    }
}