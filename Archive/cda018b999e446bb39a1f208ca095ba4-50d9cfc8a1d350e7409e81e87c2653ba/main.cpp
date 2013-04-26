#include <limits.h>
#include <stdlib.h>     /* malloc, free, rand */
#include <stdio.h>
#include <string>
#include <iostream>     // std::cout
#include <utility>      // std::pair
#include <functional>   // std::equal_to
#include <algorithm>    // std::mismat
#include <vector>

#ifndef SHAPE
#define SHAPE

struct Color {
    Color( unsigned char r, unsigned char g, unsigned char b ) 
    : red( r ), green( g ),     blue( b ) {
    }
    Color() : red( 0 ), green( 0 ), blue( 0 ) {
    }
    unsigned char red, green, blue;
};

class Shape{
private:
    Color color;
public:
    Shape (const Color & col) : color(col){}
//    virtual void Draw(Image & figure) const = 0;

};

class Line : public Shape{
public:
    Line (int x1, int y1, int x2, int y2, const Color & color);
//    virtual void Draw(Image & figure) const;

private:
    int x1, y1, x2, y2;
};
#endif // SHAPE

Line::Line( int x1, int y1, int x2, int y2, const Color &color )
    : x1( x1 )
    , x2( x2 )
    , y1( y1 )
    , y2( y2 )
    , Shape(color){
}

int main()
{
    std::cout<<"Test";
  return 0;
}