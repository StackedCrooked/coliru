template<class T>
class toto{
    T a;
};

template <typename T> struct identity {using type = T;};
template <typename T>
using identity_t = typename identity<T>::type;

template<class T>
toto<T> operator+(toto<T> const&, identity_t<T> const&)
{
    return {};
}
    
int main(){
     toto<float> t;
     toto<float> d = t +2.3;
}