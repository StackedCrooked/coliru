#include <tbb/pipeline.h>
#include <array>
#include <iostream>
#include <vector>
#include <stdlib.h>


// Pipeline: this pipeline has 4 stages:
// 1. input: generates integers from 1 to 10
// 2. times-three: multiplies the input number with 3
// 3. divide-by-two: divides the intput number by 2
// 4. print: prints the resulting number


// [1]  [2]  [3]  [4]
//  1 => 3 => 1 => "1"
//  2 => 6 => 3 => "3"
//  3 => 9 => 4 => "4"
// etc...


struct InputIntegers : tbb::filter
{
    InputIntegers() :
        tbb::filter(parallel),
        integers(),
        current(begin(integers))
    {
        for (Integers::size_type i = 0; i != integers.size(); ++i)
        {
            integers[i] = i + 1;
        }
    }
    
    void* operator() (void*)
    {
        if (current == end(integers))
        {
            return nullptr;
        }
        
        return &*current++;
    }
    
    typedef std::array<int, 16> Integers;
    Integers integers;
    Integers::iterator current;
};


struct TimesThree : tbb::filter
{
    TimesThree() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        n *= 3;
        return integer;
    }
};


struct DivideByTwo : tbb::filter
{
    DivideByTwo() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        n /= 2;
        return integer;
    }
};


struct OutputFilter : tbb::filter
{
    OutputFilter() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        std::cout << n << ' ';
        return nullptr;
    }
};


int main()
{    
    // create the filter objects for the pipeline
    InputIntegers input;
    TimesThree times_three;
    DivideByTwo divide_by_two;
    OutputFilter output;

    // create the pipeline and insert filter
    tbb::pipeline pipeline;
    pipeline.add_filter(input);    
    pipeline.add_filter(times_three);
    pipeline.add_filter(divide_by_two);
    pipeline.add_filter(output);

    // N is the maximal number of pieces a pipeline could process at one time
    pipeline.run(4); 

    // clear the pipeline before destruction
    pipeline.clear();
}
