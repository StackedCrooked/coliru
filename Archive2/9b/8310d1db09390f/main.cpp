#include <iostream>
#include <functional>
#include <type_traits>
#include <vector>

template<typename T>
class Signal;

template<typename R, typename... Args>
class Signal<R(Args...)>
{
private:
   typedef std::function<R(Args...)> Slot;

   std::vector<Slot> slots;

public:
   Signal();

   void connect( Slot slot );
   R emit(Args... args) const;

   template <typename T = R>
   typename std::enable_if<sizeof...(Args) != 0 && std::is_same<T,R>::value, R>::type
   emit(Args... args) const
   {
      for( typename std::vector<Slot>::iterator i = this->slots.begin(); i != this->slots.end(); i++ ) {
         (*i)( args... );
      }
   }

   template <typename T = R>
   typename std::enable_if<sizeof...(Args) == 0 && std::is_same<T,R>::value, R>::type
   emit() const
   {
      for( typename std::vector<Slot>::iterator i = this->slots.begin(); i != this->slots.end(); i++ ) {
         (*i)();
      }
   }

   template <typename T = R>
   typename std::enable_if<sizeof...(Args) != 0 && std::is_same<T,R>::value, R>::type
   operator()(Args... args) const
   {
      this->emit(args...);
   }

   template <typename T = R>
   typename std::enable_if<sizeof...(Args) == 0 && std::is_same<T,R>::value, R>::type
   operator()() const
   {
      this->emit();
   }
};

void anyFunc(int num) {
   // Do nothing here!
}

int main()
{  
    Signal<void(int)> signal;
    signal.connect(anyFunc);

    signal.connect(
          [] (int num) {
             // TODO: Implement handler logic here.
          }
    );
    signal.emit( 0 );
    
    return 0;
}
