template<class T, class U = bool> struct X;
template<class T = int, class U> struct X{};

int main(){
    X<>{};
}