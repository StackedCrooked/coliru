#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


typedef std::vector<int> Array;


int binarySearchRecursive(Array arr, int lower, int upper, int target)
{
 
 if (lower > upper)
 {
     cout<<"wrong range!"<<endl;
     return -1;
 }
 
 if (arr[lower] > arr[upper])
 {
     cout<<"Not sorted!"<<endl;
     return -1;
 }
 
 
 if (lower==upper && target!=arr[lower])
 {
     cout<<"target was not found"<<endl;
     return -1;
 }
 
 int cur = int((lower+upper)/2);
 if ( arr[cur] == target )
 {
     return cur;
 }
 else if (arr[cur] < target)
 {
     lower = cur+1;
     return binarySearchRecursive(arr, lower, upper, target);
 }
 else
 {
     upper = cur-1;
     return binarySearchRecursive(arr, lower, upper, target);
 }
    
}





int binarySearch(Array arr, int lower, int upper, int target)
{
    // wrong index order
 if (lower > upper)
 {
    return -1;
 }
 
 
 // target is out of range
 if (arr[lower]>target || arr[upper] < target)
 {
    return -1;     
 }

int cur;
while (1) {
    // verify that the array is sorted
    if (arr[upper] < arr[lower])
    return -1;
    
    cur = int((lower+upper)/2);
  
    if (lower >= upper && arr[cur] != target )
    {
      return -1;
    } 

  
    if (arr[cur] == target)
    {
        return cur;
    }
    else if (arr[cur] > target)
    {
        upper = cur-1;
    }
    else
    {
        lower = cur+1;
    }
    
    cout<<"arr[cur] = "<<arr[cur]<<endl;
    cout<<"cur = "<<cur<<endl;
    cout<<"arr[upper] = "<<arr[upper]<<endl;
    cout<<"upper = "<<upper<<endl;
    
    /*
    if (upper-1 <= 2)
      cout<<"smaller or equal. Cur = "<<cur<<"  Upper: "<<upper<<endl;
    else
      cout<<"Larger. Cur = "<<cur<<"  Upper: "<<upper<<endl;
    */
    cout<<endl;
          
   } 

/*
if (arr[lower]==target)
return lower;

if (arr[upper]==target)
return upper;
*/    
    
//return -1;
}


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "ddd!"
    };
    std::cout << words << std::endl;
    
    
    Array sortedNumbers = { 1, 3, 5, 7};
    std::cout<<"the array content is: "<<sortedNumbers<<std::endl;
    
    int targetIndex = binarySearchRecursive(sortedNumbers, 0, sortedNumbers.size()-1, 0);
    std::cout<<"The target index is: "<<targetIndex<<std::endl;
    
}
