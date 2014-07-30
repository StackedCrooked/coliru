#include <iostream>
#include <functional>
using namespace std;

template <typename ReturnType, typename... Args>
auto CallIt( std::function<ReturnType( Args... )> method ) -> std::function<ReturnType( Args... )>
{
    return method;
}



int main() {

    std::function<bool(int,int)> lambda = [] ( int a, int b ) { return a > b; };
    
    auto test = CallIt( lambda );
    cout << test(4,1);


    return 0;
}