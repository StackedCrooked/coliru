
#define _SCL_SECURE_NO_WARNINGS
#define BOOST_DISABLE_ASSERTS 
#include <boost/multi_array.hpp>

#include <sys/time.h>

unsigned GetTickCount()
{
        struct timeval tv;
        if(gettimeofday(&tv, NULL) != 0)
                return 0;

        return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}

int main(int argc, char* argv[])
{
    const int X_SIZE = 200;
    const int Y_SIZE = 200;
    const int ITERATIONS = 500;
    unsigned int startTime = 0;
    unsigned int endTime = 0;

    // Create the boost array
    typedef boost::multi_array<double, 2> ImageArrayType;
    ImageArrayType boostMatrix(boost::extents[X_SIZE][Y_SIZE]);

    // Create the native array
    double *nativeMatrix = new double [X_SIZE * Y_SIZE];

    //------------------Measure boost----------------------------------------------
    startTime = ::GetTickCount();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        for (int y = 0; y < Y_SIZE; ++y)
        {
            for (int x = 0; x < X_SIZE; ++x)
            {
                boostMatrix[x][y] = 2.345;
            }
        }
    }
    endTime = ::GetTickCount();
    printf("[Boost] Elapsed time: %6.3f seconds\n", (endTime - startTime) / 1000.0);

    //------------------Measure native-----------------------------------------------
    startTime = ::GetTickCount();
    for (int i = 0; i < ITERATIONS; ++i)
    {
        for (int y = 0; y < Y_SIZE; ++y)
        {
            for (int x = 0; x < X_SIZE; ++x)
            {
                nativeMatrix[x + (y * X_SIZE)] = 2.345;
            }
        }
    }
    endTime = ::GetTickCount();
    printf("[Native]Elapsed time: %6.3f seconds\n", (endTime - startTime) / 1000.0);

    return 0;
}