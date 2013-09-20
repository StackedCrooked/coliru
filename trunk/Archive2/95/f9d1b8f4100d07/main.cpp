template<class F>
struct C{
    F f;
};

template<class F>
C<F> make_C(F f){
    return {f};
}

int main(){
    auto c = make_C([]{ /* ... */ }); // tadaa
    (void)c;
}