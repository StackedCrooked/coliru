#include <iostream>
#include <cassert>

using ID = int;

struct PCB {
    ID id;
};

template <typename T>
class Queue{
  private:
    struct Elem {
        T obj;
        Elem *sled;
        Elem(const T& t)
          : obj(t),
          sled(nullptr)
        { }
    };
  
    Elem *head = nullptr;
    Elem *tail = nullptr;

  public:
    
    void push_back(const T& t) {
        auto e = new Elem(t);
        if (head == nullptr) {
            assert(tail == nullptr);
            head = tail = e;
        } else {
            tail->sled = e;
            tail = e;
        }
    }
    
    T* get(ID id){
        for(Elem* tek = head; tek != nullptr; tek = tek->sled ){
            if(id == tek->obj.id ){ // <--- ERROR: `id` is not member of '<template class>'
                return &tek->obj;
            }
        }
        return nullptr;
    }
};
    
int main() {
    Queue<PCB> q;
    q.push_back(PCB{1234});
    q.push_back(PCB{5678});
    assert( q.get(1234) != nullptr );
    assert( q.get(5678) != nullptr );
    assert( q.get(2468) == nullptr );
}
