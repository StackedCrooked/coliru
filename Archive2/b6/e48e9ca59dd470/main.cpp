#include <cstdio>
#include <cmath>

int main(){
    int solution = 0;
    const int n = 1000000;
    
    double x1=0;
    double y1=1;
    double x2=1;
    double y2=n;
    double x=1;
    double y=n;
    
    if (x1 < y1 && x1 > 0.1)
        printf("%.0lf/%.0lf",x1,y1);
    if (x2 < y2 && x2 > 0.1)
        printf(" %.0lf/%.0lf",x2,y2);
    while (y!=1.0)
    {
        x = std::floor((y1 + n) / y2) * x2 - x1;
        y = std::floor((y1 + n) / y2) * y2 - y1;
        if (x < y && x > 0.1)
            printf(", %.0lf/%.0lf",x,y);
        x1 = x2, x2 = x, y1 = y2, y2 = y;
    }
}