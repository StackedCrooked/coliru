#include <vector> 


// functions are undefined and thus unoptimizable
void disappear(int);
std::vector<int> get_data();



#ifdef USE_ITERATOR


// Vector algorithm.
typedef std::vector<int>::iterator FwdIt;

void process(FwdIt begin, FwdIt end)
{
    for (FwdIt it = begin; it != end; ++it)
    {
        disappear(*it);
    }
}


#else // USE_ITERATOR


// Pointer algorithm.
void process(int* begin, int* end)
{
    for (int* it = begin; it != end; ++it)
    {
        disappear(*it);        
    }
}


#endif // USE_ITERATOR


int main()
{    
    std::vector<int> data = get_data();
    
#ifdef USE_ITERATOR    
    process(data.begin(), data.end()); // Use vector::iterator
#else
    process(&data[0], &data[0] + data.size()); // Use raw pointer
#endif
}

