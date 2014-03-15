#include <limits>

int main()
{    
    int i { long { std::numeric_limits<long>::max () } };
}