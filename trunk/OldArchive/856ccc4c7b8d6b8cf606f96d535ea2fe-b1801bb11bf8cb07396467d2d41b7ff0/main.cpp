#include <vector>

// functions are undefined and thus unoptimizable
void disappear(int); 
std::vector<int> get_vector();


#ifdef USE_ITERATOR
template<typename It>
void process(It begin, It end)
{
    for (It it = begin; it != end; ++it)
    {
        disappear(*it);
    }
}
#else
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
    std::vector<int> v = get_vector();
    
#ifdef USE_ITERATOR
    process(v.begin(), v.end());
#else
    process(&v[0], &v[0] + v.size());
#endif
}

