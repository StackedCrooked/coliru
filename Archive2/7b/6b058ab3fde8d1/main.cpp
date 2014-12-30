
constexpr int square(int x);       //OK, declaration
struct pixel {           // error: pixel is a type
    int x;
    int y;
     pixel(int);            // OK, declaration
};

 pixel::pixel(int a)
    : x(square(a)), y(square(a)) { } //OK, definition
 pixel small(2);          // error: square not defined, so small(2)
                                     // not constant (5.19 [expr.const]), so constexpr not satisfied
constexpr int square(int x) {      // OK, definition
    return x * x;
}
 pixel large(4);          // OK, square defined

int main()
{
    
}