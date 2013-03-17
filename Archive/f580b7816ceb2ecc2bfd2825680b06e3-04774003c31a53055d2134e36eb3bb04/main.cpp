namespace X{
namespace Y{
  struct foo{};
}
  void bar(Y::foo);

}

void bar(...);

int main(){
    X::Y::foo f;
    bar(f);
}