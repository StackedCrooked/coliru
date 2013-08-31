
#include <thread>
#include <map>
#include <mutex>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <chrono>
#include <memory>
using namespace std;

typedef map<int, int*> MapOfIntIntPtr;

struct MapWrapper {
  private:
    // mutable/const in C++11 is not the same as in C++98 
    // ref: http://herbsutter.com/2013/05/28/gotw-6b-solution-const-correctness-part-2/
    mutable MapOfIntIntPtr _map;   
    mutable mutex _mutex;
  public:
    int* Find(int index) const {
      auto found = _map.find(index);    
      if (found == _map.end()) {
          return found->second;
      }
      return nullptr;
    }
    
    void Add(int index, int valueForPtr) {
        auto lock = unique_lock<mutex>{_mutex};
        _map[index] = new int(valueForPtr);
    }
    
    
    // Only SAFE by convention. Here the index represents the thread_id
    // if we follow the convention the below operations are OK. If we do not 
    // follow the conventions and another thread tries to do this with the wrong
    // index then it is very, very bad.
    void ClearValue(int index) const {
        int* found = Find(index);
        delete found;
        found = nullptr; // for checking later
    }
    
};

void AddStuff(MapWrapper& wrapper, int index) {
    wrapper.Add(index, index);   // mutex protected since it adds elements and can invalidate iterators
    std::chrono::milliseconds wait(10);
    std::this_thread::sleep_for(wait);
    wrapper.ClearValue(index); // not mutex protected: does not add/delete number of elements
}

int main() {
    
    map<int, shared_ptr<std::thread>> safetyCheck;
    MapWrapper importantStuff;
    
    
   for (size_t index = 0; index < 10; ++index) {
        safetyCheck[index] = shared_ptr<thread>(new std::thread(AddStuff, std::ref(importantStuff), index));
        cout << index << " ";
    }
  cout << "\n\n\n Joining: " << endl;
  for (size_t index = 0; index < 10; ++index) {
        auto& t = safetyCheck[index];
        t->join();
        cout << index << " ";
    }

 for (size_t index = 0; index < 10; ++index) {
     int* found = importantStuff.Find(index);
     assert(found == nullptr);
 }
    cout << "\n Success \n" << endl;
    
    return 0;
}