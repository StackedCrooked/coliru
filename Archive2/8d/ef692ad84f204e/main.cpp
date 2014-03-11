#include <iostream>
#include <stdio.h>

struct Point {
    int x, y;
};

struct Rect {
    int x, y, w, h;
};

class InputStream {
    private:
    char* flow;
    
    public:
    InputStream(char* flow) {
        this->flow = flow;
    }
    
    Point* readPoint() {
        Point *point = (Point*)flow;
        flow += 8;
        return point;
    }
    
    Rect* readRect() {
        Rect *rect = (Rect*)flow;
        flow += 16;
        return rect;
    }
};

char data[16*2+32*2] = {
        //Point1
        11, 0, 0, 0, //x = 11
        12, 0, 0, 0, //y = 12
        //Rect1
        21, 0, 0, 0, //x = 21
        22, 0, 0, 0, //y = 22
        23, 0, 0, 0, //w = 23
        24, 0, 0, 0, //h = 24
        //Point2
        31, 0, 0, 0, //x = 31
        32, 0, 0, 0, //y = 32
        //Rect3
        41, 0, 0, 0, //x = 41
        42, 0, 0, 0, //y = 42
        43, 0, 0, 0, //w = 43
        44, 0, 0, 0, //h = 44
    };

int main(int argc, char* argv[]){
    InputStream is(data);
    Point *point;
    Rect *rect;
    
    point = is.readPoint();
    printf("%s\nx=%d; y=%d;\n\n","point1", point->x, point->y);
    
    rect = is.readRect();
    printf("%s\nx=%d; y=%d;\nw=%d; h=%d;\n\n","rect1", rect->x, rect->y, rect->w, rect->h);
    
    point = is.readPoint();
    printf("%s\nx=%d; y=%d;\n\n","point2", point->x, point->y);
    
    rect = is.readRect();
    printf("%s\nx=%d; y=%d;\nw=%d; h=%d;\n\n","rect2", rect->x, rect->y, rect->w, rect->h);
}