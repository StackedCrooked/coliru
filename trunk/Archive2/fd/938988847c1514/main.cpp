
#include <string>
#include <iostream>
#include <queue>
#include <mutex>
#include <thread>
#include <algorithm>
#include <future>
#include <utility>
 
double accum(std::vector<double>::iterator beg, std::vector<double>::iterator end, double init)
{
    return std::accumulate(beg,end,init);
}

double comp2(std::vector<double>& v)
{
    using Task_type = double(std::vector<double>::iterator,std::vector<double>::iterator,double);

    if ( v.size() < 10 )
    {
        return std::accumulate(v.begin(),v.end(),0.0);
    }
    else
    {
        std::packaged_task<Task_type> pt0{accum};
        std::packaged_task<Task_type> pt1{accum};

        std::future<double> f0 {pt0.get_future()};
        std::future<double> f1 {pt1.get_future()};

        std::vector<double>::iterator mid( v.begin() );
        for(std::size_t i=0; i<v.size()/2;i++) ++mid;
        std::thread t1 {std::move(pt0),v.begin(),mid,0.0};
        std::thread t2 {std::move(pt1),++mid,v.end(),0.0};

        t1.join();
        t2.join();

        return f0.get()+f1.get();
    }
}

int main(int argc, char *argv[])
{
    std::vector<double> v {1.0,2.0,3.0,4.0,5.0,6.0,7.0};
    std::cout << "sum = " << comp2(v) << std::endl;
    return 0;
}
