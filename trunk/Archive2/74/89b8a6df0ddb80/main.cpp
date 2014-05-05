#include <iostream>
#include <vector>
#include <map>

// Forward declaration
template <typename> void magic();


template <typename T>
struct Magic {
    static void m(){
        std::cout << "Called magic<T>" << std::endl;
    }
};

template <typename T>
struct Magic<std::vector<T> > {
    static void m(){
        std::cout << "Called magic<std::vector<T> >" << std::endl;
        magic<T>();
    }
};

template <typename T, typename U>
struct Magic<std::map<T,U> > {
    static void m(){
        std::cout << "Called magic<std::vector<T> >" << std::endl;
        magic<T>();
        magic<U>();
    }
};

template <typename T>
void magic() {
    Magic<T>::m();
}

int main() {
    magic<std::vector<std::map<std::string,std::vector<int> > > >();
}
