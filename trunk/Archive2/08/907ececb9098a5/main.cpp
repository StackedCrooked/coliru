#include <iterator>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>

void shift_down(std::vector<int>& v, int i, int s){     
        while ( i*2 + 1 < s ) { 
            int child = 2*i + 1; 
            if ((child + 1 < s) && v[child] < v[child+1]) child++;
        if (v[i] < v[child]) {   
            std::swap(v[i],v[child]); 
            i = child;  
        }        
        else            
            return;    
    }
} 

void heap_sort(std::vector<int>& v, int s){          
    for (int i = s/2; i >= 0; i--) { 
        shift_down(v, i, s);    
    }
    while (s-1 > 0) {  
        std::swap(v[s-1], v[0]);
        shift_down(v, 0, s-1);  
        s--;
    }
}  


int main(){
    std::vector<int> vec {2, 5, 1, 49, 32, 9, 0, -1};
    int size = vec.size();

    heap_sort(vec,size);  
    std::copy(vec.begin(),vec.end(),
          std::ostream_iterator<int>(std::cout, "\t"));
    std::cout<<"\t"<<std::endl;

    return 0;
}