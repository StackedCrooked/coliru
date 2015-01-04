#include <vector>
#include <iostream> 

template <typename Iter, typename Cont>
bool isLast(Iter iter, const Cont& cont) {
    return (iter != cont.end()) && (next(iter) == cont.end());
}

template <typename T>
struct is_cont {
    static const bool value = false;
};
template <typename T,typename Alloc>
struct is_cont<std::vector<T,Alloc> > {
    static const bool value = true;
};

template <typename T, typename std::enable_if< !is_cont<typename T::value_type>::value>::type* = nullptr >
std::string printContainer(T const& container)
{
    std::string str = "{";
    for (auto it = std::begin(container); it != std::end(container); ++ it)
        str += (isLast(it, container) ? std::to_string(*it) + "}" : str += std::to_string(*it) + ",");
    return str;
}

template <typename T, typename std::enable_if< is_cont<typename T::value_type>::value>::type* = nullptr >
std::string printContainer(T const& container)
{
    std::string str = "{"; 
    for (auto it = std::begin(container); it != std::end(container); ++ it)
        str += (isLast(it, container) ? printContainer(*it) + "}" : str += printContainer(*it) + ",");
    return str;
}

template <class T, class cmp=std::greater<T>>
class Foo
{
private:
    std::vector<T> data_;
public:
    typedef typename std::vector<T>::value_type  value_type;

    Foo(size_t n, T val) : data_(n, val) {}
    typename std::vector<T>::iterator begin(){ return data_.begin(); } // for printContainer
    typename std::vector<T>::iterator end()  { return data_.end();   }   // for printContainer
    
    typename std::vector<T>::const_iterator begin() const { return data_.cbegin(); } // for printContainer
    typename std::vector<T>::const_iterator end() const { return data_.cend();   }   // for printContainer
};

int main()
{
    std::vector<std::vector<float>> a(2,std::vector<float>(3,3));
    std::cout << printContainer(a) << std::endl; // it works !

    Foo<float> b(10,2);
    for (auto it = std::begin(b); it != std::end(b); it ++)
        std::cout << *it << " ";  // it works !

     std::cout << printContainer(b) << std::endl;  // but this does not work !
}