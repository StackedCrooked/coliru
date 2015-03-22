#include <vector>
using container = std::vector<int>;
const int size  = 1000000;
const int count = 1000;

#ifdef MYOWNFLAG
void foo(std::insert_iterator<container> ist)
{
    for(int i=0; i<size; ++i)
        *ist++ = i;
}
#endif

void bar(container& cnt)
{
    for(int i=0; i<size; ++i)
        cnt.push_back(i);
}
int main()
{
    container cnt;
    for (int i=0; i<count; ++i)
    {
        cnt.clear();
        bar(cnt);
    }
    return 0;
}
