#include <iostream>
#include <vector>
#include <memory> 
#include <map>
 
using namespace std;
 
typedef int ContainedType;
 
int main() {
 
    auto_ptr<vector<ContainedType> > open_vec(new vector<ContainedType>);
 
    open_vec->push_back(5);
    open_vec->push_back(3);
    open_vec->push_back(1);
 
    // Transfers control, but now the vector cannot be changed:
    auto_ptr<const vector<ContainedType> > closed_vec(open_vec); 
 
    //for( size_t i=0; i<open_vec->size(); ++i)
     //   cout << open_vec->at(i) << endl;
     
    auto_ptr<vector<ContainedType> > new_vec( const_cast<vector<ContainedType>* >(closed_vec)); 
    for( size_t i=0; i<new_vec->size(); ++i)
          cout << open_vec->at(i) << endl;
    
    // closed_vec->push_back(8); // Can no longer modify 
 
    // Safe during the lifetime of the autoptr:
    map<string, const ContainedType *> nmap;
 
    nmap["First"]  = & closed_vec->at(0);
    nmap["Second"] = & closed_vec->at(1);
    nmap["Third"]  = & closed_vec->at(2);
 
    for (map<string, const ContainedType *>::iterator it = nmap.begin(); it != nmap.end(); ++it) {
        cout << it->first << " -> " << *(it->second) << std::endl;
    }
 
    return 0;
}
