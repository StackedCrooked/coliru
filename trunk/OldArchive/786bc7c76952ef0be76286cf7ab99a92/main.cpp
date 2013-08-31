#include <type_traits>

template<typename Iterator>
void solve_world_hunger(Iterator it)
{
    auto lambda = [](typename std::add_const<decltype(*it)>::type x){
        auto y = x;   // this should work
        x = x;        // this should fail
    };
}

int main(){
    
    int y = 42;
    int* x = &y;
    solve_world_hunger(x);
}