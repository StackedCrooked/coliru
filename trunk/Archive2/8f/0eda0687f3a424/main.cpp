#include <set>
#include <boost/range/algorithm.hpp>
#include <boost/function_output_iterator.hpp>
#include <cassert>

void do_something(int) {}

int main()
{
    const std::set<int> src1 { 1,2,3 }, 
                        src2 { 1,9 };

    unsigned total = 0;

    boost::set_difference(src1, src2, boost::make_function_output_iterator([&](int i) 
                { 
                    total+= i*i; 
                }));

    assert(total == 13);
}
