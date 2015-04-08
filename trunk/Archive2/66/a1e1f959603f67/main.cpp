#include <iostream>
#include <boost/coroutine/all.hpp>


int main()
{
    boost::coroutines::asymmetric_coroutine<int>::pull_type source(
    [&](boost::coroutines::asymmetric_coroutine<int>::push_type& sink){
        int first=1,second=1;
        sink(first);
        sink(second);
        for(int i=0;i<8;++i){
            int third=first+second;
            first=second;
            second=third;
            sink(third);
        }
    });

    for(auto i:source)
        std::cout << i <<  " ";
}
