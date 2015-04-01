#include <iostream>
#include <ctime>
#include <chrono>


using namespace std::chrono;
using Clock = std::chrono::steady_clock;


using volatile_double = volatile double;


volatile_double X[1024][1024];
volatile_double Y [1024][1024];


long linear_cost;
long jump_cost;


int main()
{
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(i=0;i<1024;i++) for(j=0;j<1024;j++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "linear access   : " << cost << std::endl;
        linear_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(i=0;i<1024;i++) for(j=0;j<1024;j++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "linear access   : " << cost << std::endl;
        linear_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(j=0;j<1024;j++) for(i=0;i<1024;i++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "nonlinear access: " << cost << std::endl;
        jump_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(j=0;j<1024;j++) for(i=0;i<1024;i++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "nonlinear access: " << cost << std::endl;
        jump_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(i=0;i<1024;i++) for(j=0;j<1024;j++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "linear access   : " << cost << std::endl;
        linear_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(i=0;i<1024;i++) for(j=0;j<1024;j++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "linear access   : " << cost << std::endl;
        linear_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(j=0;j<1024;j++) for(i=0;i<1024;i++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "nonlinear access: " << cost << std::endl;
        jump_cost += cost;
    }
    { 
        auto start_time = Clock::now();
        int i,j; for (int a = 0; a != 10; ++a) for(j=0;j<1024;j++) for(i=0;i<1024;i++) X[i][j] = Y[i][j];
        auto cost = duration_cast<std::chrono::microseconds>(Clock::now() - start_time).count();
        std::cout << "nonlinear access: " << cost << std::endl;
        jump_cost += cost;
    }
    
    std::cout << "\ntotal cost of  linear access: " << linear_cost
              << "\ntotal cost of  jumpy  access: " << jump_cost
              << " (x" << int(0.5 + 1.0 * jump_cost / linear_cost) << ")"
              << std::endl;

    return X[rand() % 1024][rand() % 1024] + Y[rand() % 1024][rand() % 1024];
}
