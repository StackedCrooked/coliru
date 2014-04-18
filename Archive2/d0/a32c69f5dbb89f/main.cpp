#include <iostream>
#include <chrono>
#include <iomanip>

const int fact[] = {1, 1, 2, 6, 24, 120, 720};

void compute()
{
    int abc;
    int facts;
    for(int a=0;a<=6;a++){
        for(int b=0;b<=6;b++){
            for(int c=0;c<=6;c++){
                abc = (100*a)+(10*b)+c;
                facts = fact[a] + fact[b] + fact[c];
                if(abc==facts)
                    std::cout<<"nums are: "<<a<<","<<b<<","<<c<<'\n';
            }
        }
    }
}

int main()
{
    auto begin = std::chrono::high_resolution_clock::now();
    compute();
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin);
    std::cout << "took " << std::fixed << (dur.count()/1000000000.0) << "s to find\n";
    return 0;
}