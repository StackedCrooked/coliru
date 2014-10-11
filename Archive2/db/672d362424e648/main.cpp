

struct Point
{
    Point(int x, int y) : x(x), y(y) {}
    
    int x() const { return x; }
    
    int y() const { return y; }
    
private:
    int x, y;
};


struct Size
{
    Size(int width, int height) : width(width), height(height) {}
    
    int width() const { return width; }
    
    int height() const { return height; }
    
private:
    int width, height
};


int main()
{
    Point p(1, 2);
    Width w(3, 4);
}