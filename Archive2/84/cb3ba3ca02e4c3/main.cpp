#include <iostream>
#include <functional>
#include <boost/function.hpp>
#include <boost/bind.hpp>

namespace tbb {

    template<typename Item>
    struct parallel_do_feeder {  };
    
    struct task_group_context {
    };

    namespace internal {
        template<typename Iterator, typename Body, typename Item> 
        void select_parallel_do( Iterator first, Iterator last, const Body& body, void (Body::*)(Item) const

            , task_group_context& context 

            )
        {
            //run_parallel_do(...)
        }
    }
    
    template<typename Iterator, typename Body> 
    void parallel_do( Iterator first, Iterator last, const Body& body, task_group_context& context  )
    {
        if ( first == last )
            return;
        internal::select_parallel_do( first, last, body, &Body::operator(), context );
    }
}

void print_item(int32_t& item) {
    std::cout << "value: " << item << std::cout;
}

int main(int argc,char** argv)
{
    tbb::task_group_context group_context;
    std::vector<int32_t> foo = {1,2,3,4,5,6,7};
    std::function<void (int32_t&)> printer = std::bind(&print_item,std::placeholders::_1);
    tbb::parallel_do(foo.begin(),foo.end(),printer,group_context);
}