#include <iostream>
#include <string>
#include <vector>

#include <sys/time.h>
#include <ctime>

#define LENGTH 10000000
struct A
{
    int x;
    int y;
    int z;
    int r;
    int g;
    int b;
};

struct B
{
    int x[LENGTH];
    int y[LENGTH];
    int z[LENGTH];
    int r[LENGTH];
    int g[LENGTH];
    int b[LENGTH];
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

int main()
{
    std::vector<struct A> a;
    for (int i = 0; i < LENGTH; ++i) {
        struct A tmp = {0,0,0,0,0,0};
        a.push_back(tmp);
    }
    
    struct timeval tv;
    unsigned int endms, startms;
    
    gettimeofday(&tv, NULL);
    startms = tv.tv_usec;
    startms /= 1000;
    startms += (tv.tv_sec * 1000);
    
    int sum = 0;
    for (int i = 0; i < LENGTH; ++i) {
        sum += a[i].x + a[i].y + a[i].z + a[i].r + a[i].g + a[i].b;
    }
    
    gettimeofday(&tv, NULL);
    endms = tv.tv_usec;
    endms /= 1000;
    endms += (tv.tv_sec * 1000);
    
    std::cout << "AoS time: " << endms-startms << " ms." << std::endl;
    std::cout << "AoS time: " << startms << " ms." << std::endl;
    std::cout << "AoS time: " << endms << " ms." << std::endl;
    
    struct B b;
    for (int i = 0; i < LENGTH; ++i) {
        b.x[i] = 0;
        b.y[i] = 0;
        b.z[i] = 0;
        b.r[i] = 0;
        b.g[i] = 0;
        b.b[i] = 0;
    }
 
    gettimeofday(&tv, NULL);
    startms = tv.tv_usec;
    startms /= 1000;
    startms += (tv.tv_sec * 1000);
    
    sum = 0;
    for (int i = 0; i < LENGTH; ++i) {
        sum += b.x[i] + b.y[i] + b.z[i] + b.r[i] + b.g[i] + b.b[i];
    }

    gettimeofday(&tv, NULL);
    endms = tv.tv_usec;
    endms /= 1000;
    endms += (tv.tv_sec * 1000);
    
    std::cout << "\nSoA time: " << endms-startms << " ms." << std::endl;
    std::cout << "SoA time: " << startms << " ms." << std::endl;
    std::cout << "SoA time: " << endms << " ms." << std::endl;
}