class Rect {
    int _width = 0, _height = 0;
    
public:
    Rect(int w, int h) : _width{w}, _height{h} {}    
    int width() const { return _width; } 
    int height() const { return _height; }
    void resize(int w, int h) { _width = w; _height = h; }
};

int area(const Rect & r) { return r.width() * r.height(); }

int main()
{
    Rect r(3, 4);
    
    // Which of the following operations labeled
    // A, B, C and D are thread-safe? Why (not)?
    r.width();      // A
    r.height();     // B
    r.resize(4, 5); // C
    area(r);        // D
}