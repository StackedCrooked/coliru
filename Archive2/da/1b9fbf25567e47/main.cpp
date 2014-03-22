#include <tbb/pipeline.h>
#include <array>
#include <iostream>
#include <vector>
#include <stdlib.h>


//Pipeline: n -> n *= 3 -> n /= 2 -> print n


class InputFilter : public tbb::filter
{
public:
    InputFilter() : tbb::filter(parallel), counter(0) { }
    
    void* operator() (void*)
    {
        // send maximum 10 segements
        if (counter < 10)
        {
            return new int(counter++);
        }
        
        // last segment must be null 
        return nullptr;
    }
    
    int counter;    
};


class TimesThree : public tbb::filter
{
public:
    TimesThree() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        n *= 3;
        return integer;
    }
};


class DivideByTwo : public tbb::filter
{
public:
    DivideByTwo() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        n /= 2;
        return integer;
    }
};


class OutputFilter : public tbb::filter
{
public:
    OutputFilter() : tbb::filter(parallel) { }
    
    void* operator() (void* integer)
    {
        int& n = *static_cast<int*>(integer);
        std::cout << n << ' ';
        delete (&n);
        return nullptr;
    }
};


int main()
{
    
    // create the filter objects for the pipeline
    InputFilter input;
    TimesThree times_three;
    DivideByTwo divide_by_two;
    OutputFilter output;
     
    // create the pipeline and insert filter
    tbb::pipeline pipeline;
    pipeline.add_filter(input);    
    pipeline.add_filter(times_three);
    pipeline.add_filter(divide_by_two);
    pipeline.add_filter(output);
     
    // N is the maximal number of segmentsta pieces a pipeline could process at one time
    pipeline.run(4); 
    
    // clear the pipeline before destruction
    pipeline.clear();
}