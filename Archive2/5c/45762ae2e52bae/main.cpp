template<class T> struct X;
template<class T = int> struct X{};

int main(){
    X<> x;
}