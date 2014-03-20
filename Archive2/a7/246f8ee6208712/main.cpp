#include<iostream>

class Iterator{    
public: 
  Iterator (int i_) : i(i_) 
  {}

  bool operator!=(const Iterator &other) const {
    return i != other.i;
  }

  int operator*() const{
    return i; 
  }

  void operator++(){
    ++i;
  }

private:
  int i; 
};

struct Generator{

  Iterator begin()
  {
    return Iterator(0); 
  }

  Iterator end(){
    return Iterator(100); 
  }
}; 

int main(){

  Generator g; 

  for (int i : g)
    {
      // do something. 
    }

}