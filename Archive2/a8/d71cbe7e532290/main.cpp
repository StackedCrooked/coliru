struct Foo;

template<typename> Foo* Func(){return nullptr;}

template<typename... TArgs>
void SomeFunc() {
   Foo* data[] = {
     Func<TArgs>()..., // <- expand the pack into array but calling Func for each type
     nullptr
   };
}

int main(){
    SomeFunc<int,double>();
    SomeFunc<>();
}