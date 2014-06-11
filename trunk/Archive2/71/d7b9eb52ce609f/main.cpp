#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
int main()
{
    int loss_count=0;
    int loss_percent=10;
    int num_exper=1000;
    std::random_device rd;
    std::mt19937 gen(rd());
    gen.seed( rd() );
    std::uniform_int_distribution<> dis(0,100);
    std::normal_distribution<> d(loss_percent,2);
    std::map<int, int> hist;
    for(int k=0;k<num_exper;k++){
        loss_count=0;
        loss_percent=std::round(d(gen));
        for(int n=0; n<1000; ++n) {
            if(round(dis(gen))<loss_percent)
            {
                 loss_count++;
                 
            }
              
        }
         ++hist[loss_count];
    }
    for(auto p : hist) {
        std::cout << std::fixed << std::setprecision(1) << std::setw(2)
                  << p.first << ' ' << std::string(p.second/1, '*') << '\n';
    }
}