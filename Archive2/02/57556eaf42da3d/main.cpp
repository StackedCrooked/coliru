#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include <thread>
#include <functional>

template <typename Tp>
void selection_sort(Tp* vals, size_t sz) {
    for(size_t i = 0; i < sz; i++) {
        size_t min_idx = i;
        Tp min = vals[i];
        for(size_t j = i+1; j < sz; j++) {
            if(vals[j] < min) {
                min = vals[j];
                min_idx = j;
            }
        }
        
        Tp a = vals[min_idx];
        vals[min_idx] = vals[i];
        vals[i] = a;
    }
}

template <typename Tp>
void bubble_sort(Tp* vals, size_t sz) {
    for(size_t n = 0; n < sz; n++) {
        for(size_t i = 1; i < sz; i++) {
            if(vals[i-1] > vals[i]) {
                Tp a = vals[i-1];
                vals[i-1] = vals[i];
                vals[i] = a;
            }
        }
    }
}

template <typename Tp>
void insertion_sort(Tp* vals, size_t sz) {
    for(size_t i = 1; i < sz; i++) {
        Tp test = vals[i];
        size_t j = i;
        while(j > 0 && vals[j-1] > test) {
            vals[j] = vals[j-1];
            j--;
        }
        vals[j] = test;
    }
}



template <typename Tp>
Tp* merge_down(Tp* a, size_t sa, Tp* b, size_t sb) {
    bool afree = false, bfree = false;
    
    std::thread at;
    std::thread bt;
    
    if(sa > 1) {
        at = std::thread([&]() {
            a = merge_down(a, sa/2, a+sa/2, (sa+1)/2);
        });
        afree = true;
    }
    if(sb > 1) {
        bt = std::thread([&]() {
            b = merge_down(b, sb/2, b+sb/2, (sb+1)/2);
        });
        bfree = true;
    }
    
    if(afree)
        at.join();
    if(bfree)
        bt.join();
    
    Tp* out = new Tp[sa+sb];
    size_t i = 0, j = 0, o = 0;
    
    while(i < sa || j < sb) {
        if(i < sa && j < sb) {
            if(a[i] < b[j])
                out[o] = a[i++];
            else
                out[o] = b[j++];
        }
        else if(i < sa)
            out[o] = a[i++];
        else if(j < sb)
            out[o] = b[j++];
        
        o++;
    }

    if(afree)
        delete[] a;
    if(bfree)
        delete[] b;
    
    return out;
}

template <typename Tp>
void merge_sort(Tp* vals, size_t sz) {
    Tp* out = merge_down(vals, sz/2, vals+sz/2, (sz+1)/2);
    std::copy(out,out+sz,vals);
    delete[] out;
}

int main() {
    int vals[] = {100,99,44,33,21,1231,123,123,312,12,412,12,412,412,512,31,314,10,9,8,7,6,5,4,3,2,1};
    merge_sort(vals, sizeof(vals)/sizeof(int));
    
    for(size_t i = 0; i < sizeof(vals)/sizeof(int); i++) {
        std::cout << vals[i] << " ";
    }
    std::cout << std::endl;
}
