#include <iostream>
#include <functional>
#include <boost/function.hpp>
#include <boost/bind.hpp>

template<typename Item>
struct parallel_do_feeder {
};

struct task_group_context {
};

void print_item(int32_t& item) {
    std::cout << "value: " << item << std::cout;
}

template<typename Iterator,typename Body,typename Item,typename _Item>
void select_parallel_do(Iterator first, Iterator last, const Body& body, void (Body::*)(Item, parallel_do_feeder<_Item>&) const, task_group_context& context)
{
    
}

template<typename Iterator,typename Body>
void parallel_do(Iterator first,Iterator last,const Body& body)
{
    if ( first == last ) {
        return;
    }
    task_group_context context;
    select_parallel_do( first, last, body, &Body::operator(), context);
}

int main(int argc,char** argv)
{
    std::vector<int32_t> foo = {1,2,3,4,5,6,7};
    boost::function<void(int32_t&)> printer = boost::bind(&print_item,_1);
    parallel_do(foo.begin(),foo.end(),printer);
}