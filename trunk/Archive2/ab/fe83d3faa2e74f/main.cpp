

struct Point
{
    Point(int x, int y) : data{x, y} {}
    
    int x() const { return data.x; }
    
    int y() const { return data.y; }
    
private:
    struct datum { int x, y; } data;
};


struct Size
{
    Size(int width, int height): data{width, height} {}
    
    int width() const { return data.width; }
    
    int height() const { return data.height; }
    
private:
    struct datum { int width, height; } data;
};


int main()
{
    Point p(1, 2);
    Size w(3, 4);
}