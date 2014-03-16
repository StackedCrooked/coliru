#include <cstddef>
#include <new>
#include <memory>
#include <iostream>

typedef char* region_ptr;

//seriously, this is one situation where I would find a global justified
 region_ptr region;

 //store these in the memory region
 //but you can pretend they're actual pointers
 template<class T>
 struct offset_ptr { 
     offset_ptr() : offset(0) {}

     T* get() const {return (T*)((char*)region + offset);}
     void set(T* ptr) {offset = (char*)ptr - (char*)region;}

     offset_ptr(T* ptr) {set(ptr);}
     offset_ptr& operator=(T* ptr) {set(ptr); return *this;}
     operator T*() const {return get();}
     T* operator->() const {return get();}
     T& operator*() const {return *get();}
     
 private:
     ptrdiff_t offset;
 };
 template<class T>
 struct offset_delete {
     typedef offset_ptr<T> pointer;
     void operator()(offset_ptr<T> ptr) const {ptr->~T();}
 };
 
 struct node {
     int a;
     offset_ptr<node> next;
     offset_ptr<node> prev;
     
     ~node() {std::cout << "dtor\n";}
 };
 
 
 int main() {
     char buffer[10000];
     region = buffer;
     
     node* nodes = new ((node*)region + 0) node(); //construct first node
                   new ((node*)region + 1) node(); //construct second node
     
     nodes->next = &nodes[1]; //assign offset_ptr from node*
     nodes[1].prev = nodes;
     
     nodes->next->a = 2; //using operator-> on the offset_ptr
     
     std::unique_ptr<node, offset_delete<node>> nodeptr0(nodes);
     std::unique_ptr<node, offset_delete<node>> nodeptr1(nodes+1);
 }