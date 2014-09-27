#include <iostream>

template<typename T, typename... U>
struct tuple{
    T first;
    tuple<U...> second;
    tuple()=default;
    tuple(T t, U... u):first(t), second(u...){}
    std::ostream& print(std::ostream& stream) const{
        stream<<first<<", ";
        return second.print(stream);
    }
};

template<typename T>
struct tuple<T>{
    T first;
    tuple()=default;
    tuple(T t):first(t){}
    operator T&(){
        return first;
    }
    std::ostream& print(std::ostream& stream) const{
        return stream<<first;
    }
};

template<typename... T>
std::ostream& operator<<(std::ostream &stream, const tuple<T...> &out){
    stream<<'(';
    return out.print(stream)<<")";
}

template<typename... T>
inline auto mk_tuple(T... t){
    return tuple<T...>(t...);
}

int main(){
    std::cout<<mk_tuple(1, 2, 3, "xyz", 'c');
}
