#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
/* 
int main()
{
    
    std::vector<std::pair<int, std::string> > v = { {2, "baz"},
                                                   {2, "bar"},
                                                   {1, "foo"} };
    std::sort(v.begin(), v.end());
 
    for(auto p: v) {
        std::cout << "(" << p.first << "," << p.second << ")\n";
    }
    
}
*/

// typedef std::pair<int, int>  PairList;
// typedef std::vector<PairList> DependencyList;
using namespace std;
typedef std::vector<std::pair<int, int>> DependencyList;

void SearchList( DependencyList &dl)
{
    
for (DependencyList::iterator dl_iter=dl.begin(); dl_iter != dl.end(); ++dl_iter)
   {    
        std::cout << dl_iter->first << "," << dl_iter->second <<"\n";
                
   }   
}

void  getMinimalDependencyList( DependencyList& dl);

int main()
{
    DependencyList dl = { {2, 3},{3, 4},{2,4},{4,5},{5,1} };
    std::sort(dl.begin(), dl.end());
   
    getMinimalDependencyList(dl);
    
}

void  getMinimalDependencyList(DependencyList& dl)
{

    int size=dl.size(); cout<<"Vector Size is "<<size<<"\n";
    // int f, s; 
    std::pair<int,int> temp;
    static DependencyList dc; 
    
    for (int i=0; i < size; i++)
    {
       
    if(dl[i].first == dl[i+1].first)
     {
            cout<< "Duplicate Elemement At \n"<<i<<","<<i+1<<"\n";
            cout<< "Duplicate Pair is {"<<dl[i].first<<","<<dl[i].second<<"}\n";
            cout<< "Duplicate Pair is {"<<dl[i+1].first<<","<<dl[i+1].second<<"}\n";
          //  f=dl[i].second;s=dl[i+1].second; 
            
            temp=std::make_pair(dl[i].second,dl[i+1].second);
    
     cout<< i <<"\n";            
     
     for (DependencyList::iterator dl_iter=dl.begin(); dl_iter != dl.end(); ++dl_iter)
      {
          
           std::cout << dl_iter->first << "," << dl_iter->second <<"\n";
           
           if (*dl_iter == temp)
              {
                 cout<<"\nCommon Pair Found\n";                        
                 std::cout << dl_iter->first << "," << dl_iter->second <<"\n\n";
                        
                 
              } 
          
       
       }
    
    } // if
            
    } // for
    
    dl.erase(dl.begin()+1);
     
    std::cout <<" \n\nRevised Vector List \n";
        
    for (DependencyList::iterator dl_iter=dl.begin(); dl_iter != dl.end(); ++dl_iter)
      {
              std::cout << dl_iter->first << "," << dl_iter->second <<"\n";
      }      
    
// return  dl;
    
}

