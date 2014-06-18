template<class T, class U, class V = double> class A;
template<class T, class U = bool, class V> class A;
template<class T = int, class U, class V> class A {};

int main(){
    A<>{};
}