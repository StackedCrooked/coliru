// testVect.cpp : ZM, Nov 2013, Tests #pragma ivdep on loop with conditionals
// This is actually demonstrating ivdep for INTEL COMPILER (but uses Coliru just
// for sharing convinience)
#include <iostream>
#include <vector>
#include <chrono>
#include <vector>
#include <climits>

//Play with it in order to model different type conversions
typedef char mytype;
typedef unsigned int UINT;

//Non-vectorized version, returns number of elements below c_thresh
int foo(int n,    float * f, mytype* c, mytype c_thresh)
{
    int counter = 0;
    for ( int i = 0; i < n; ++i )
    {
        if ( c[i] < c_thresh )
		{
			f[i] = 0.0f;
			counter++;
		}
        else
		{
			f[i] = 1.0f;
		}
    }
	return counter;
}

//Overloaded vectorized version, returns number of elements below c_thresh
int foo(int n,	float * f, mytype* c, mytype c_thresh, bool wantsVector /* = anyValueYouWant*/)
{
	int counter = 0;
    //Instead of #pragma ivdep, one could use #pragma simd or  restrict -like keywords
    #pragma ivdep
    for ( int i = 0; i < n; ++i )
    {
        if ( c[i] < c_thresh ){
			f[i] = 0.0f;
			counter++;
		}
        else
		{
			f[i] = 1.0f;
		}
    }
	return counter;
}

int main(int argc, char* argv[])
{
	const int n = 64000000;

	float * f = new float[n];
	mytype* c = new mytype[n];

	mytype c_thresh = 0;

    //No seed/generator init - just test run
    for(int k = 0; k < n; ++k) {
            c[k] = mytype (rand() % UCHAR_MAX);
			//c[k] = k % 256; 
	}

	//warm-up run
	foo(n, f, c, c_thresh);

	//non-vectorized run
    auto startTime = std::chrono::high_resolution_clock::now();
	int counter = foo(n, f, c, c_thresh);
    auto endTime = std::chrono::high_resolution_clock::now();

    //Disabled time stamps output, because coliru doesn't use gcc4.9; and gcc4.9 is expected to be first version supporting pragma simd or pragma ivdep. This code compiles
    // with ICL14, providing at least 5x speed-up (No-vector vs. Vector) for SSE Vectorization.
    std::cout << "No-vector : " <</*" calculations took " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count() << "ms , " << */ "counter = " << counter << std::endl;


	//vectorized run (same input data; vectorized only with ICL, Cray/PGI or (expected in future) gcc4.9!)
    startTime = std::chrono::high_resolution_clock::now();
	counter = foo(n, f, c, c_thresh, true);
    endTime = std::chrono::high_resolution_clock::now();
	std::cout << "Vector: " << /*"Vector calculations took " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime-startTime).count() << "ms ," <<*/ "counter = " << counter << std::endl;

	return 0;
}
