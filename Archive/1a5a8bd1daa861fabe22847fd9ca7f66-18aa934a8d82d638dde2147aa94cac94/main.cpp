#include <algorithm>
#include <vector>
#include <array>
#include <iostream>
#include <cassert>

template<class Elem>
void print_arr(Elem* arr, unsigned int r) {
    for(unsigned i=0; i<=r; ++i)
        std::clog << arr[i] << ' ';
}

template<class Elem, class Comp>
void mergeRecurse(Elem* arr, Elem* tmp, unsigned int l, unsigned int r, const Comp& lt)
{
    std::clog << "mergeRecurse({";
    print_arr(arr,r);
    std::clog << "},tmp," << l << ',' << r << ")\n";
    
    unsigned int mid;
    unsigned int i;
    unsigned int j;
    unsigned int k;

    if (l < r)
    {        
        mid = l + (r - l) / 2;
        mergeRecurse(arr,tmp,l,mid,lt);
        mergeRecurse(arr,tmp,mid+1,r,lt);

        for (i = l; i <= mid; i++)
        {
            tmp[i] = arr[i];
        }

        for (j = r; j > mid; j--)
        {
            tmp[j] = arr[j];
        }

        for (i = l, j = r, k = l; k <= r; k++)
        {
            if (lt(tmp[j], tmp[i]))
            {
                arr[k] = tmp[j--];
            }
            else
            {
                arr[k] = tmp[i++];
            }
        }
    }
}


void do_test(std::vector<int> data) { //makes a copy
    std::clog << "begin: ";
    print_arr(&data[0],data.size()-1);
    std::clog << '\n';
    std::vector<int> tmp(data.size());    
    mergeRecurse(&data[0], &tmp[0], 0, data.size()-1, std::less<int>()); 
    std::clog << "end: ";
    print_arr(&data[0],data.size()-1);
    std::clog << '\n';
    assert(std::is_sorted(data.begin(), data.end()));
}

void do_minimal_tests() {
    std::array<std::vector<int>,15> sets = {{
        {0},
        {0, 0},
        {0, 1},
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 1},
        {0, 1, 2},
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 1},
        {0, 1, 1, 1},
        {0, 0, 1, 2},
        {0, 1, 1, 2},
        {0, 1, 2, 2},
        {0, 1, 2, 3}
    }};
    for(unsigned i=0; i<sets.size(); ++i) {        
        std::vector<int> t=sets[i];
        do {
            do_test(static_cast<std::vector<int>&>(t));
        }while(std::next_permutation(t.begin(),t.end()));
    }
}

int main() {
    do_minimal_tests();
}