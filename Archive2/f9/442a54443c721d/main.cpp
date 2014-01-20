
#include <iostream>
#include <functional> 
#include <memory>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;
 
 struct A
 {
     int a;
 };

int main()
{
   
   vector<shared_ptr<A>>    v;
   
   for(int i = 0; i < 1000 ; i++)
        v.push_back(make_shared<A>());
    
    auto p = make_shared<A>();
    v.push_back(p);
    
    cout << "before: "<<v.size()<<endl;
    
    v.erase(std::remove(v.begin(), v.end(), p), v.end());
    
    cout << "after: "<<v.size()<<endl;
}
 
