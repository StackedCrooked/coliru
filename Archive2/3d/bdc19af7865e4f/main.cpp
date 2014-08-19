#include <boost/lockfree/spsc_queue.hpp>
#include <iostream>
#include <vector>

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) { for (auto& el : vec) os << el << ' '; return os; }

enum way_of_pop
{
    output_iterator, // C++ style
    output_buffer    // C style
};


void test(way_of_pop wop)
{
    std::vector<int> src = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    // make a queue with 10 capacity
    boost::lockfree::spsc_queue<int> queue(10);
    
    // push the 10 numbers
    queue.push(src.begin(), src.end());

    // using vector as pop destination
    std::vector<int> dst;

    if (wop == output_buffer)
    {   
        // make buffer with size of half the queue
        dst.resize(src.size() / 2); 
        
        queue.pop(dst.data(), dst.size());
    }
    else if (wop == output_iterator)
    {
        // reserve storage for half the queue
        dst.reserve(src.size() / 2);
        
        // use back_inserter to create output iterator
        queue.pop(std::back_inserter(dst));
    }
    else
    {
        // program is a failure, performing seppuku
        *((int*)0) = 1;
    }
    
    std::cout << "popped: " << dst << std::endl;
}


int main()
{
    test(output_buffer);
    test(output_iterator);
}

