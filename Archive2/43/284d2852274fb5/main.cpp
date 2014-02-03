#include <iostream>
struct point{double x; double y;};

int main() {
    double n1, n2; //temporary data for user entry
    int pcount = 0; //size of my array
    point *p = new point[0]; //my array
    point *tmp; //temporary array while resizing
    
    while (points >> n1 >> n2){//for each element the user enters,  
        tmp = new point[pcount+1]; //allocate memory for the new array
        for(int i=0; i<pcount; ++i) //copy the elements from the old to the temporary
            tmp[i] = p[i];
        delete[] p; //delete the old array
        p = tmp; //point p at the new array
        p[pcount].x = n1; //now push back the new element
        p[pcount].y = n2;
        ++pcount; //increase the array size
    }
    
    delete[] p;
}