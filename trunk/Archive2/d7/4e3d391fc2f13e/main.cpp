struct {
  unsigned field:1;
} dummy = {0};

template<class T> struct X{};

template<class T>
X<T> foo(T&&){ return X<T>(); }

int main(){
  struct{}_ = foo(dummy.field);
}