#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

double square(double in)
{
    return in*in;
}

int main(int,char **)
{
    std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};
    
    double sum_x = std::accumulate( x.begin(), x.end(), 0.0 );

    double x_bar = sum_x / static_cast<double>(x.size());

    std::cout << "mean = " << x_bar << std::endl;

    std::cout << "x" << std::endl;
    std::for_each(x.begin(), x.end(),
                  [](double &elem){std::cout << elem << " ";}
        );
    std::cout << std::endl;

    double sum_xmxb = std::accumulate(x.begin(), x.end(), 0.0, 
                               std::bind(
                                   std::plus<double>(),
                                   std::placeholders::_1,
                                   std::bind(
                                        std::minus<double>(),
                                        std::placeholders::_2,
                                        x_bar)
                                        )
                                    );
                                         
    std::cout << "sum (x-x_bar) = " << sum_xmxb << std::endl; 
    
    double variance = std::accumulate(x.begin(),x.end(),0.0,
                                std::bind(
                                    [=](double& init,double& elem){return init + (elem-x_bar)*(elem-x_bar);},
                                    std::placeholders::_1,
                                    std::placeholders::_2)) / (x.size()-1);
                                    
    std::cout << "variance = " << variance << std::endl;                                     
                                    
}
