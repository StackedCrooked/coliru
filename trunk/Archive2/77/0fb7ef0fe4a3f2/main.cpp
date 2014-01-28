#include <iostream>
#include <vector>


int main()
{
    std::vector<int> x = { 34, 42, 5, 1, 6 };
    
    int hi, lo;    // These are indices pointing to the highest and lowest elements
    hi = lo = 0;   // Set hi and lo to the first element's index
    
    // Then compare the elements indexed by hi and lo with the rest of the elements
    for (int i = 1;i < x.size();i++) {
        if(x[i] < x[lo]) {
            // The element indexed by i is less than the element indexed by lo
            //    so set the index of the lowest element to i
            lo = i;
        }
        else if(x[i] > x[hi]) {
            // Same logic as the above, only for the highest element
            hi = i;
        }
    }
    
    std::cout << "The lowest number is " << x[lo] << " at position " << lo << ".\n";
    std::cout << "The highest number is " << x[hi] << " at position " << hi << ".\n";
}
