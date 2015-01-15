#include <iostream>
#include <cassert>
#include <stdexcept>

struct rectangle {
    virtual ~rectangle() = default;
    
    virtual void set_width(int value) {
        width = value;
    }
    
    virtual void set_height(int value) {
        height = value;
    }
    
    virtual void set_size(int width, int height) {
        set_width(width);
        set_height(height);
    }
    
    int width, height;
};

struct square : rectangle {
    virtual void set_width(int value) override {
        set_height(value);
    }
    
    virtual void set_height(int value) override {
        height = value;
        width = value;
    }
    
    virtual void set_size(int width, int height) override {
        if (width != height) {
            throw std::runtime_error("you suck");
        }
        
        set_height(height);
    }
};

void frob_rectangle(rectangle& r) {
    r.set_width(100);
    r.set_height(300);
}

void frob_square(rectangle& r) {
    r.set_width(200);
}

void frob_bad_square(rectangle& r) {
    r.set_size(100, 200);
}

int main()
{
    square s;
    rectangle r;
    
    frob_rectangle(r);
    assert(r.width == 100 && r.height == 300);
    frob_rectangle(s);
    assert(s.width == 300 && s.height == 300);
    frob_square(r);
    assert(r.width == 200 && r.width == 200);
    frob_square(s);
    assert(s.width == 200 && s.width == 200);
    frob_bad_square(r);
    assert(r.width == 100 && r.height == 200);
    try {
        frob_bad_square(s);
        std::cout << "broken\n";
    } catch (const std::runtime_error&) {
        std::cout << "womp womp womp\n";
    }
}
