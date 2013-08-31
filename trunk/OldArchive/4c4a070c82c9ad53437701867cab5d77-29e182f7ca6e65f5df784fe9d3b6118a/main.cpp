template<class T>
void f(T){}

template<class A, class B, class... C>
void f(A, B b, C... c){
    f(b, c...);
}

int main(){
    f(1,2,3,4,5,6,7,8);
}