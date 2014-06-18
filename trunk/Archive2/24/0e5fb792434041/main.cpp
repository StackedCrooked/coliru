template<class T, class U, class V = double> struct X;
template<class T, class U = bool, class V> struct X;
template<class T = int, class U, class V> struct X{};

int main(){
    X<>{};
}