#include <iostream>
#include <string>
#include <typeinfo>
#include <ctime>
#include <cmath>
#include <chrono>

int main()
{
    // Example code for testing subnormal float efficency
    float f = 2.0f;
    std::chrono::steady_clock::duration prevdiff;
    for (int k = 0; k < 10000; ++k) {            
        float sum = .0f;
    		
    	auto start = std::chrono::steady_clock::now();
    
    	for (int n = 0; n < 1e7; ++n) {
    		sum += f * 0.1f;
    	}

    	auto end = std::chrono::steady_clock::now();
    	auto diff = end - start;
    	std::cout << k << ", f=" << f << ", isnormal=" << std::isnormal(f)
    		<< ", elapsed=" << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" <<
    		", ratio=" << (prevdiff.count() == 0 ? 0 : (diff.count() / prevdiff.count())) << std::endl;
    	prevdiff = diff;
    
    	if (f < std::numeric_limits<float>::min())
    		break;
    
    	f /= 2.0f;
    }

}