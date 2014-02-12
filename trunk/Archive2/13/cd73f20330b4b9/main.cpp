#include <cstdio>

int main() {
    int s, p, d;
    scanf("%d %d %d", &s, &p, &d);
    while((s < 1) | (s > 15000) | (p < 1) | (p > 4000) | (d < 1) | (d > 15000)){
        printf ("prekroceny limit \n");
        return 1;//scanf("%d %d %d", &s, &p, &d);
    }   
}