#include <iostream>
#include <stdio.h>

struct Point {
    int x, y;
};

void printBytes(char* arr, unsigned int count) {
    for(unsigned int i = 0; i < count-1; i++) {
        printf("%d, ",*arr++);
    }
    printf("%d\n",*arr);
}

char data[16] = {11, 0, 0, 0, 22, 0, 0, 0, 33, 0, 0, 0, 44, 0, 0, 0};

int main(int argc, char* argv[]){
    Point point[2];
    
    point[0].x = 101;
    point[0].y = 102;
    point[1].x = 103;
    point[1].y = 104;
    
    char *flow = (char*)point;
    unsigned int size = sizeof point;
    
    printBytes(flow, size);
    
    Point *pointFlow = (Point*)data;
    
    printf("point[0].x = %d; point[0].y = %d;\n", pointFlow[0].x, pointFlow[0].y);
    printf("point[1].x = %d; point[1].y = %d;\n", pointFlow[1].x, pointFlow[1].y);
    
    std::cout<<"work";
}