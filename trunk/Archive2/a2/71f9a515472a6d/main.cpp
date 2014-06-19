#include <iostream>

template<class Priority, class T> class PriorityQueue {
  class Iterator {
    
  };
public:
  using iterator = Iterator;
  //some methods
  Iterator begin() const;
  Iterator end() const;
};

template<class Priority,class T>
typename PriorityQueue<Priority, T>::iterator PriorityQueue<Priority,T>::begin() const {
    return Iterator(); // Return right staff here
}

template<class Priority,class T>
typename PriorityQueue<Priority, T>::iterator PriorityQueue<Priority,T>::end() const{
    return Iterator(); // Return right staff here
}

auto main() -> int {
    PriorityQueue<int, int>::iterator it, ite;
    PriorityQueue<int, int> PR;
    it  = PR.begin();
    ite = PR.end();
  return 0;
}