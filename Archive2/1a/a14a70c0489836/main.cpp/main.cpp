#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <assert.h>

unsigned int count = 0;

void swap(unsigned int i, unsigned int j, std::vector<int>& A){
    if(i == j)
        return;
    assert( i < A.size());
    assert( j < A.size());
    auto first = A.begin();
    std::advance(first, i);
    auto second = A.begin();
    std::advance(second, j);
    std::iter_swap(first, second);
    
    count++;
}

int solution(std::vector<int> &A) {
    unsigned int lastSeen = 0;
    
    while(lastSeen < A.size()){
        unsigned int current = lastSeen;
        bool keepGoing = true;
        while(keepGoing){
            if( (A.at(current) != A.size()+1) && (A.at(current) != current+1) ){
                unsigned int next = A.at(current) - 1;
                swap(current, next, A);
            }
            else
                keepGoing = false;
        }
        
        ++lastSeen;
    }
    
    for(unsigned int i = 0; i < A.size(); ++i)
        if(A.at(i) != i + 1)
            return i+1;
        
    return A.size() + 1;
}

int main(){
    std::vector<int> in = {16, 17, 18, 19, 7, 2, 3, 8, 20, 14, 1, 9, 5, 10, 4, 6, 11, 13, 15};
    
    auto res = solution(in);
    std::cout << "----------------" << std::endl;
    std::cout << res << std::endl;
    std::cout << "count = " << count << std::endl;
}
