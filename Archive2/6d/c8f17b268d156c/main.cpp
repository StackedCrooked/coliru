#include <iostream>
#include <chrono>

int main()
{
    for(int divisors=1; divisors<=500; ++divisors)
    {
        auto start = std::chrono::steady_clock::now();
        
        int num=0;
        int sqrt_rnd_up = 1;            
        for(int i=1; ;++i) 
        {
            num += i;
            int div = 0;
            int test_max = sqrt_rnd_up*sqrt_rnd_up;
            if (test_max < num)
                ++sqrt_rnd_up;
            if (test_max == num)
                ++div;
            //std::cerr << "newmax: " << sqrt_rnd_up << '\n';
            for(int j=1; j<sqrt_rnd_up; j++)
            {
                if (num%j == 0) {
                    //std::cerr << j << " divides " << num << "\n";
                    div+=2;
                }
            }
            if(div >= divisors)
                break;
        }
        
        auto stop = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cerr << "found that " << num << "\thas " << divisors << "\tdivisors in " << duration.count() << "ms\n";
    }
    return 0;
}