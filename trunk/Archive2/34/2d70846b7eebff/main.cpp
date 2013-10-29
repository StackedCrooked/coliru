#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<int> v;
    v.push_back(20);
    v.push_back(7);
    v.push_back(11);
    v.push_back(9);
    v.push_back(10);
    
    vector<int>::value_type AnInt;
    
    cout << "--- Member Types ---" << endl << endl;
    
        cout << "value_type = " << AnInt << endl;
        
    
    cout << "--- Member Functions ---" << endl << endl;
    
        cout << "size of vector = " << v.size() << endl; 
        cout << "capacity of vector = " << v.capacity() << endl;
        cout << "max_size = " << v.max_size() << endl;
        cout << "Empty = " << v.empty() << endl << endl;
        
        v.shrink_to_fit();
        
        cout << "--vector shrink to fit--" << endl;
        cout << "size of vector = " << v.size() << endl; 
        cout << "capacity of vector = " << v.capacity() << endl << endl;
        
        v.resize(10);
        
        cout << "--vector got resized--" << endl;
        cout << "size of vector = " << v.size() << endl; 
        cout << "capacity of vector = " << v.capacity() << endl << endl;
        
        v.reserve(20);
        
        cout << "--vector reserved memory--" << endl;
        cout << "size of vector = " << v.size() << endl; 
        cout << "capacity of vector = " << v.capacity() << endl << endl;
        
   
   return 0;
}