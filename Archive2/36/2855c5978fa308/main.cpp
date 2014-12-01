#include <iostream>
#include <vector>

int main() {
    std::vector<int> myvector;
    myvector.push_back (1);
    myvector.push_back (2);
    myvector.push_back (3);//here the size is 3
    myvector.erase(myvector.begin()+1);//I think normally the size should be 2 after removing the element
    std::cout << myvector.size();
    
    return 0;
}