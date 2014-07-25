#include <iostream>
#include <ctime>


long[] a = {1., 1., 2., 3., 5., 8., 13., 21., 34., 55., 89., 144., 233., 377., 610., 987., 1597., 2584., 4181., 6765., 10946., 17711., 28657., 46368., 75025., 121393., 196418., 317811., 514229., 832040.};

int canMerge(int t1, int t2) {
    long lowFib = min(t1, t2);
    long highFib = max(t1, t2);
    return (highFib <= 2 * lowFib ) && (highFib==1 || highFib != lowFib);
}


int sum(int a,int b)
{
    std::cout << a+b << std::endl;
}

std::clock_t time(int (&foo)(int,int))
{
    std::clock_t start = std::clock();
    int q=1,w=2;
    foo(q,w);
    std::clock_t end = std::clock();
    std::cout << "Time:" <<  (end - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
}

int main()
{

time(sum);
return 0;

}
