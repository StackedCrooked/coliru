#include <cstring>

template <typename T>
inline T const& max (T const& a, T const& b)
{
    return a < b ? b : a;
}

// maximum of two C-strings (call-by-value)
inline char const* max (char const* a, char const* b)
{
    return strcmp(a,b) < 0 ? b : a;
}

// maximum of three values of any type (call-by-reference)
template <typename T>
inline T const& max (T const& a, T const& b, T const& c)
{
    return max (max(a,b), c); 
}

int main ()
{
    ::max(7, 42, 68);  
}
