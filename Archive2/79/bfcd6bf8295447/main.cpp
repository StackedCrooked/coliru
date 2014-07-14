#include <new>

class MyClass
{
    public:
        MyClass(int i) : p(i) {}
    private:
        int p;
};

int main(int argc, char** argv) {
  
  void* buff10 = operator new[](sizeof(MyClass) * 10); 
  
  MyClass * arr = static_cast<MyClass*>(buff10);
  
  for(std::size_t i = 0 ; i < 10 ; ++i)
    new (arr + 1) MyClass(i);
    
  // Use it ...
    
  // Then delete :
  
  for(int i = 0 ; i >= 0 ; --i)
      arr[i].~MyClass();
      
  operator delete[] (arr);
      
  return 0;
}