#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int cosa(vector<int> v, int num){
    std::cout << num + 1 << "\n";
    v.insert(v.begin()+v.size(),6);
    for (int n: v){
        std::cout << n << ' ';}
    std::cout << '\n';
    return 0;
}

int * d_fun(vector<int> v){
    int b = v.size();
    int arreglo[b];
    int *holi = arreglo;
    copy(v.begin(), v.end(), arreglo);
    return holi;
}

int main()
{
    std::vector<int> v{0,1,2,3,4,5}; 
    int k;
    int h = v.size();
    
    int arr[v.size()];
    copy(v.begin(), v.end(), arr);
    for (int n:arr) cout << arr[n] <<" ";
    //pasar vector a arreglo
    cout << "\n";
    
    for (k=1; k<h;++k){
        // simple rotation to the left
        std::rotate(v.begin()+1, v.begin() + 2, v.end());
     
        std::cout << "simple rotate left  : ";
        for (int n: v)
            std::cout << n << ' ';
        std::cout << '\n';
    }
    cosa(v, 5);
    
    cout << d_fun(v)[4];
 
}