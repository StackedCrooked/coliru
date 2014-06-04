#include <iostream>
#include <stdio.h>

class Drawable {
    public:
    virtual ~Drawable(){};
    virtual void draw(){};
};


class Rect: public Drawable {
    protected:
    int x, y, width, height;
    public:    
    Rect(int x, int y, int width, int height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    
    int getX() {
        return x;
    }
    
    int getY() {
        return y;
    }
    
    int getWidth() {
        return width;
    }
    
    int getHeight() {
        return height;
    }
};

/*
class Brick: public Rect {
    public:
    Brick():Rect(1,1,100,100) {
    }
};
*/

class Brick: public Rect {
    public:
    Brick():Rect(1,1,100,100) {
    }
};


int main(int argc, char* argv[]){
    Brick brick = Brick();
    printf("x = %d\ny = %d\nw = %d\nh = %d", brick.getX(), brick.getY(), brick.getWidth(), brick.getHeight());
}