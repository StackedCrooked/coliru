#include <iostream>
#include <vector>
 
void print_vec(const std::vector<int>& vec)
{
    for (auto x: vec) {
         std::cout << ' ' << x;
    }
    std::cout << '\n';
}
 
int main ()
{
    int arr[] = { 501,502,503 };
    std::vector<int> vec(arr,arr+3);
    print_vec(vec);
    
    std::vector<int>::const_iterator it = vec.begin();
    
    (++++++++it++++++++);
    
    std::cout << *it;
}