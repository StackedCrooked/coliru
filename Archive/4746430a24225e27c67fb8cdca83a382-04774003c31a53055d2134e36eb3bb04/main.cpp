namespace X{
namespace Y{
  struct foo{};
  void bar(foo);
}

}

void bar(X::Y::foo);

int main(){
    X::Y::foo f;
    bar(f);
}