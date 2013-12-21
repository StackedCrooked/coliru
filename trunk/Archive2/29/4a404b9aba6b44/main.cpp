#include <climits>
#include <iostream>
#include <chrono>
#include <random>

// Needed to time things.
#define START_TIMER std::chrono::system_clock::time_point t0 = \
std::chrono::system_clock::now();
#define END_TIMER    std::chrono::system_clock::time_point t1 = std::chrono::system_clock::now();
#define ELAPSED_TIME std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0).count()

const int NUM_SAMPLES = 100000000;

struct Point {
    
    private:
        std::default_random_engine rng;
        std::uniform_real_distribution<double> uniform;

    public:
        double x;
        double y;

    void next() {
        x = double(rng())/UINT32_MAX;
        y = double(rng())/UINT32_MAX;
    }
    
    int inside_circle() {
        return (((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5))<0.25) ? 1 : 0;
    }
};

int main()
{
    double pi = 0.0;

    START_TIMER
    
    Point p;
    int count = 0; // Count of how many darts fall inside/outside circle.
	for (int n = 0; n<NUM_SAMPLES; n++) {

        // Throw a dart at the unit square!
        p.next();
        count += p.inside_circle();
	}
    
	// Calculating pi
	pi = 4.0 * count / NUM_SAMPLES;
	
    END_TIMER
    
    std::cout << "Estimated value of PI (using " << NUM_SAMPLES << " random samples): "<< pi;
    std::cout << " calculated in " << ELAPSED_TIME << " ms" << std::endl;
	
	return 0;
}

// Typical program output is shown below ...
//
// Estimated value of PI (using 100000000 random samples): 3.14192 calculated in 2265 ms

// Copyright (C) 2013, Andrew J. T. Sheppard, all rights reserved.

