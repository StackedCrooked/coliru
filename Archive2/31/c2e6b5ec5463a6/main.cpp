template<int N> struct X : X<N-1>{};
template<> struct X<0>{};

int main(){
    X<255> x;
}