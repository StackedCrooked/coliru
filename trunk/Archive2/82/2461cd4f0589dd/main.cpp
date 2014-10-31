#include <iostream>
#include <algorithm>
#include <vector>


namespace dpol
{ // destruction policies
    template<typename Func>
    struct Destruction
    {
        Func finalize; 
        
        Destruction(Func f) : finalize(f)
        {
        }
        template<typename T>
        void apply(T* data)
        {
            if (data) finalize(data); 
        }
    };
    template<>
    struct Destruction<void>
    {
        template<typename T>
        void apply(T* data)
        {
            delete data; 
        }
    };
} // destruction policies

class Wraiiper
{
    struct ResourceConcept
    {
        virtual ~ResourceConcept() {}
        virtual void* get() = 0; 
    };    
        
    template<typename T, typename Func>
    struct ResourceModel : ResourceConcept, dpol::Destruction<Func>
    {
        T* data; 
        
        template<typename U>
        ResourceModel(U* data)
            : data(data)
        { // a. One arg constructor
        }
        template<typename U, typename F>
        ResourceModel(U* data, F f)
            : dpol::Destruction<Func>(f)
            , data(data)
        { // b. Two args constructor
        }
        ~ResourceModel()
        {
            dpol::Destruction<Func>::apply(data); 
        }
        
        void* get()
        {
            return data; 
        }
    };
    
    std::vector<ResourceConcept*> resource; 
    
public:
  
  template<typename T, typename Func>
  Wraiiper(T* data, Func f)
  {
      resource.push_back(new ResourceModel<T, Func>(data, f)); 
  }
  template<typename T>
  Wraiiper(T* data)
  {
      resource.push_back(new ResourceModel<T, void>(data)); 
  }
  ~Wraiiper()
  {
      while (!resource.empty())
      {
          delete resource.back(); 
          resource.pop_back(); 
      }
  }
  
  template<typename T, typename Func>
  T* push_back(T* data, Func f)
  {
      resource.push_back(new ResourceModel<T, Func>(data, f)); 
      return get<T*>(resource.size()-1); 
  }
  template<typename T>
  T* push_back(T* data)
  {
      resource.push_back(new ResourceModel<T, void>(data)); 
      return get<T*>(resource.size()-1); 
  }
  
  template<typename T>
  T  get(std::size_t i = 0)
  {
      return (T)resource.at(0)->get(); 
  }
};

struct A
{
    int val; 
    A(int x) : val(x) {}
};

void dela(A *arg) { delete arg; }
  
int main()
{
    Wraiiper wr(new A(2), dela); // compiles fine
    Wraiiper wr2(new double);    // error !
    
    return 0;
}














