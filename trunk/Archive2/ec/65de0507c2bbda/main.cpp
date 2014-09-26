#include <iostream> 
 
struct Test
{
    int x ;
    int y ;
    Test ( int y_ ) :y(y_) , x(y*2) {
    }
};
 
int main() {
    Test t ( 10 ) ;
    std::cout << t.x << std::endl ;
    std::cout << t.y << std::endl ;
}