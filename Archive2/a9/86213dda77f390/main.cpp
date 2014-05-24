#include <functional>
#include <string>
enum MaybeType{
  Nothing,
  Just
};

template<typename T>
class Maybe{
  virtual MaybeType getType() const = 0;
};

template<typename T>
class Just : public Maybe<T>{
  T value;
  virtual MaybeType getType() const{
    return MaybeType::Just;
  }
public:
  Just(T v) : value(v){}
};

template<typename T>
class Nothing : public Maybe<T>{
  virtual MaybeType getType() const{
    return MaybeType::Nothing
  }
};

int main(){
  using namespace std;
  string s = "Hello";
  auto m = Just<string>(s); // error
}