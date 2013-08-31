#include <iostream>
using namespace std;
#define SMALL -1

struct Point {
    double x,y;
};
double get_x(Point p) {return p.x;}
double get_y(Point p) {return p.y;}
void print_pt(Point p, char c) {cout << "\n(" << p.x << ", " << p.y << ")";}
void print_p(void*arr, int sz, char c) {
    cout << c;
    for(int i=0; i<sz; ++i) 
        print_pt(*((Point*)(arr)+i), c);
}

void qs (void *arr, int left, int right, void (*swap) (void *p1, void *p2),
        int (*cmp)(void *p1, void *p2), void * (*get) (void *arr,int i))
{
    cout<<"-> "; print_p(arr,5,'2'); cout<<endl;
    int i=left, j=right;
    void *pivot=get(arr,(i+j)/2);
    while (i<=j)
    {
        while (cmp(get(arr,i),pivot)==SMALL)
            i++;
        while (cmp(get(arr,j),pivot)==1)
            j--;
        if (i<=j)
        {
         swap(get(arr,i),get(arr,j));
         i++;
         j--;
        }
    }
    if (left<j)
        qs(arr,left,j,swap,cmp,get);
    if (i<right)
        qs(arr,i,right,swap,cmp,get);
}

int comp_py(void *p1, void *p2)
{
    double p1x=get_x(*((struct Point*)p1)),
           p2x=get_x(*((struct Point*)p2)),
           p1y=get_y(*((struct Point*)p1)),
           p2y=get_y(*((struct Point*)p2));
    if (p1y>p2y)
        return 1;
    else
        if (p1y==p2y)
        {
            if (p1x>p2x)
                return 1;
            else if (p1x<p2x)
                return SMALL;
            else return 0;
            return 0;
        }
        else
            return SMALL;
}

void swap_p(void *p1, void *p2)
{
    struct Point temp=*((struct Point*)p1);
    *((struct Point*)p1)=*((struct Point*)p2);
    *((struct Point*)p2)=temp;
}

void* get_p(void *arr, int i)
{
    return ((struct Point*)arr)+i;
}

#define size 5
int main() {
    Point arr[size] = {{2.32, 23}, {-21, 23}, {-65, 34}, {34, -11}, {21, -22}};
    qs(arr,0,size-1,swap_p,comp_py,get_p);
    print_p(arr, size, '\n');
}