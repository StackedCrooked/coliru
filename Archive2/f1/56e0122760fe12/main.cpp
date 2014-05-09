#include <stdio.h>
#include <omp.h>

struct point2d {
    int x;
    int y;
    point2d(){
        x = 0;
        y = 0;
    }
    point2d(point2d& p){
        x = p.x;
        y = p.y;
    }
    
}; 

extern point2d myPoint;
#pragma omp threadprivate(myPoint)
point2d myPoint;

int main() {

    #pragma omp parallel 
    {
        //myPoint = new point2d[1];
        myPoint.x = omp_get_thread_num();
        myPoint.y = omp_get_thread_num()*10;
        #pragma omp critical
        {
            printf("thread %d myPoint->x %d myPoint->y %d\n", omp_get_thread_num(),myPoint.x, myPoint.y);
        }
    }   
    #pragma omp parallel
    {
        #pragma omp critical
        {
            printf("thread %d myPoint->x %d myPoint->y %d\n", omp_get_thread_num(),myPoint.x, myPoint.y);
        }
    }
}