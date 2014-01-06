struct Shape
{
    Shape(int x, int y, int length, char ch)
        : x(x)
        , y(y)
        , length(length)
        , ch(ch)
    {};
    
    int x, y, length;
    char ch;
};

struct Square : Shape
{
    Square(int x, int y, int length, char chIn)
        : Shape(x, y, length, ch)
    {};
};

int main() {}