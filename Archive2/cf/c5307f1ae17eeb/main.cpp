#include <iostream>
#include <vector>

struct Blah
{
    int i;
};

std::ostream& operator<<(std::ostream& os, Blah const& b)
{
    return os << b.i;
}

bool shouldElementBeRemoved(Blah const& b) { return b.i % 2; }
bool shouldElementReallyBeRemoved(Blah const& b) { return shouldElementBeRemoved(b); }

void foo(std::vector<Blah>& bvec)
{
  std::vector<std::vector<Blah>::iterator> selectedElements;
  selectedElements.reserve(bvec.size());  // avoid growing the vector while you hold a mutex lock
  
  { 
     //Critical section which holds a mutex. Should be as fast as possible
     for(auto it = bvec.begin(), it_end= bvec.end(); it != it_end; ++it)
     {
        if(shouldElementBeRemoved(*it))
           selectedElements.push_back(it);
     }
  }
  for(auto first = selectedElements.rbegin(),
           last  = selectedElements.rend();
           first != last;
           ++first)
  {
      if(shouldElementReallyBeRemoved(**first)) 
        bvec.erase(*first);
  }
}

int main()
{
    std::vector<Blah> bvec{{0}, {1}, {2}, {3}, {4}, {5}, {6}, {7}, {8}, {9}};
    
    std::cout << "Before: ";
    for(auto const& b : bvec) std::cout << b << ' ';
    std::cout << '\n';
    
    foo(bvec);
    
    std::cout << "After: ";
    for(auto const& b : bvec) std::cout << b << ' ';
    std::cout << '\n';
}
