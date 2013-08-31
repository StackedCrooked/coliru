#include <vector> 

// These function are not defined and thus not optimizable.
void disappear(int);
std::vector<int> get_data();


// The data object.
std::vector<int> data = get_data();



#ifdef USE_ITERATOR 


// Use vector iterator.
typedef std::vector<int>::iterator FwdIt;


// Use iterator algorithm.
void process(FwdIt begin, FwdIt end)
{
    for (FwdIt it = begin; it != end; ++it)
    {
        disappear(*it);
    }
}


#else 


// Use pointer algorithm.
void process(int* begin, int* end)
{
    for (int* it = begin; it != end; ++it)
    {
        disappear(*it);        
    }
}


#endif


int main()
{   
#ifdef USE_ITERATOR // => use vector::iterator

    process(data.begin(), data.end()); 

#else // => use raw pointer
    
    process(&data[0], &data[0] + data.size());
    
#endif
}

