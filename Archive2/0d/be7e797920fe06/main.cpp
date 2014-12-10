#include <chrono>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    std::size_t size = 1000000u ;
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    std::chrono::microseconds duration;
    
    {
    start = std::chrono::high_resolution_clock::now();
    float * malloc_ptr = (float *)malloc(sizeof(float)*size) ;
    end = std::chrono::high_resolution_clock::now();
    std::iota(malloc_ptr, malloc_ptr + size, 0);
    std::cout << malloc_ptr[std::rand() % size] << " ";
    free(malloc_ptr);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Malloc takes " << duration.count() << " (us)\n";
    }
    
    {
    start = std::chrono::high_resolution_clock::now();
    float * calloc_ptr = (float *)calloc(size, sizeof(float)) ;
    end = std::chrono::high_resolution_clock::now();
    std::iota(calloc_ptr, calloc_ptr + size, 0);
    std::cout << calloc_ptr[std::rand() % size] << " ";
    free(calloc_ptr);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Calloc takes " << duration.count() << " (us)\n";
    }
    
    {
    start = std::chrono::high_resolution_clock::now();
    float * new_ptr = new float[size] ;
    end = std::chrono::high_resolution_clock::now();
    std::iota(new_ptr, new_ptr + size, 0);
    std::cout << new_ptr[std::rand() % size] << " ";
    delete[] new_ptr;
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "New takes " << duration.count() << " (us)\n";
    }
    
    {
    start = std::chrono::high_resolution_clock::now();
    std::vector<float> vec1 (size);
    end = std::chrono::high_resolution_clock::now();
    std::iota(vec1.begin(), vec1.end(), 0);
    std::cout << vec1[std::rand() % size] << " ";
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Vector constructor takes " << duration.count() << " (us)\n";
    }
    
    {
    start = std::chrono::high_resolution_clock::now();
    std::vector<float> vec2;
    vec2.resize(size);
    end = std::chrono::high_resolution_clock::now();
    std::iota(vec2.begin(), vec2.end(), 0);
    std::cout << vec2[std::rand() % size] << " ";
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Vector resize takes " << duration.count() << " (us)\n";
    }
    
    {
    start = std::chrono::high_resolution_clock::now();
    std::vector<float> vec3;
    vec3.reserve(size);
    end = std::chrono::high_resolution_clock::now();
    std::fill_n(std::back_inserter(vec3), size, 0);
    std::iota(vec3.begin(), vec3.end(), 0);
    std::cout << vec3[std::rand() % size] << " ";
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "Vector reserve takes " << duration.count() << " (us)\n";
    }

}