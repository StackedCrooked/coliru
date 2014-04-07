#include <iostream>
#include <algorithm>
#include <iterator> 
#include <vector>

template<class T>
double average(std::vector<T>& elements)
{
    if(elements.empty()) return 0.0;
    double accumulator = 0.0;
    for(size_t i = 0; i < elements.size(); i++) {
      accumulator += elements[i];
    }
    return accumulator / elements.size();
}
//---------------------------------------------------------------------------
template<class T>
std::vector<std::vector<T> > group_by(std::vector<T>& elements, const int nSamples)
{
    std::vector<std::vector<T> > groups;
    std::vector<T> group;
    if(!elements.empty()) {
      for(size_t i = 0; i < elements.size(); i++) {
        if((i =! 0) && (i % nSamples) == 0) {
          groups.push_back(group);
          group.clear();
          group.push_back(elements[i]);
        }
        else {
          group.push_back(elements[i]);
        }   
      }    
      groups.push_back(group);
    }
    return groups;
}
//---------------------------------------------------------------------------
template<class T>
std::vector<T> transversal_filter(std::vector<T>& elements, const int nSamples)
{
    std::vector<T> filtered_elements;
    if(!elements.empty()) {
      std::vector<std::vector<T> > groups = group_by(elements, nSamples);
      for(size_t i = 0; i < groups.size(); i++) {
        filtered_elements.push_back(average(groups[i]));
      }
    }
    return filtered_elements;
}
//---------------------------------------------------------------------------
int main()
{
    std::vector<double> v;
    for(int i = 0; i < 20; i++) {
        v.push_back(i);
    } 
    std::vector<std::vector<double> > gs = group_by(v, 3);
    std::cout << gs.size() << std::endl;
/*    
    for(size_t i = 0; i < gs.size(); i++) {
      std::vector<double> g = gs[i];
      std::copy(g.begin(), g.end(), std::ostream_iterator<double>(std::cout, "," ));
      std::cout << std::endl;
    }
*/    
/*
    std::vector<double> fv = transversal_filter(v, 3);
    std::copy(fv.begin(), fv.end(), std::ostream_iterator<double>(std::cout, "," ));
    std::cout << std::endl;
*/
}



