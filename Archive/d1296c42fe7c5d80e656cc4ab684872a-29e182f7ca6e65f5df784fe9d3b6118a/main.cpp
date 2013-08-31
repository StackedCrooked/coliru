template<class T>
void f(T){}

template<class B, class... C>
void f(B b, C... c){
    f(c...);
}

int main(){
    f(1,2,3,4,5,6,7,8);
}