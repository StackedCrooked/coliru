#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;

void operator-=(vector<int*>& vec, size_t erased_number)
{
    size_t retained_num = 0;
    if (erased_number >= vec.size()){ retained_num = 0; }
    else{ retained_num = vec.size() - erased_number ; }

    {
    vector<int*> tmp;
    tmp.reserve(retained_num);

    copy(vec.begin(), vec.begin()+retained_num, back_inserter(tmp));
    for_each(
                vec.begin()+retained_num,
                vec.end(),
                [](int* ptr){ if(ptr) delete ptr; }
            );

    vec.swap(tmp);
    }
}

int main()
{
    vector<int*> vec(1000);
    cout<<"size="<<vec.size() << " capacity="<<vec.capacity() << endl;
    vec-=400;
    cout<<"size="<<vec.size() << " capacity="<<vec.capacity() << endl;
    vec-=700;
    cout<<"size="<<vec.size() << " capacity="<<vec.capacity() << endl;
}

