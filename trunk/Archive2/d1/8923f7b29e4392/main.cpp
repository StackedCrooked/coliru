#include <chrono>

using namespace std;
using namespace chrono;

void check(bool);


int main()
{
    // ratio difference
    {
        duration<double, nano> wide_ratio;
        duration<double, milli> narrow_ratio;
        wide_ratio = narrow_ratio;
        narrow_ratio = wide_ratio;
    }
    
    // extreme ratio difference
    {
        duration<double, pico> wide_ratio;
        duration<double, giga> narrow_ratio;
        //wide_ratio = narrow_ratio;
        //narrow_ratio = wide_ratio;
    }
    
    // 
    {
        duration<long, nano> wide_ratio;
        duration<long, micro> narrow_ratio;
        wide_ratio = narrow_ratio;
        //narrow_ratio = wide_ratio;
    }
    
    
    {
        duration<double, micro> wide_rep;
        duration<float, micro> narrow_rep;
        wide_rep = narrow_rep;
        narrow_rep = wide_rep;
    }
    
    
    {
        duration<double, micro> wide_rep;
        duration<long, micro> narrow_rep;
        wide_rep = narrow_rep;
        //narrow_rep = wide_rep;
    }
    
    {
        duration<long, micro> wide_rep;
        duration<int, micro> narrow_rep;
        wide_rep = narrow_rep;
        narrow_rep = wide_rep;
    }
}