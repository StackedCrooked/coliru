#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>

template<class iter>
void quickSort(iter first, iter last) {
    if (first==last || first+1==last)
        return;
    auto comp = std::less<typename std::iterator_traits<iter>::value_type>();
    iter pivot = std::partition(first+1, last, std::bind(comp, std::placeholders::_1, *first));
    if (first!=pivot && first+1!=pivot) {
        std::iter_swap(first, pivot-1);
        quickSort(first, pivot-1);
    }
    if (pivot!=last)
        quickSort(pivot, last);    
}

int main() {
    int myArray[] = {0, 7, 4, 1, 9, 6, 3, 2, 5, 8}; 
    quickSort(myArray+0, myArray+10); 
    std::copy(myArray+0, myArray+10,std::ostream_iterator<int>(std::cout," "));
    std::cout<<'\n';
    return 0;
}