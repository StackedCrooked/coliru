#include <string>
#include <unordered_map>

template <int N> class Object;
template <int N> class Thing;

template <int N>
class Factory {
    private:
        using FuncPtr = Object<N>*(*)(Thing<N>*);
        static std::unordered_map<std::string, FuncPtr> map;
    public:
        static void insertInMap (const std::string& tag, FuncPtr funcPtr) {
            map.emplace (tag, funcPtr);
    }
};

template <int N>
std::unordered_map<std::string, typename Factory<N>::FuncPtr> Factory<N>::map;

template class Factory<0>;

template <int N> struct Object {};

struct Blob : Object<0> {
    static Blob prototype;
    Blob() {Factory<0>::insertInMap ("Blob", Blob::create);}
    Blob (Thing<0>*) {}
    static Object<0>* create (Thing<0>* x) {return new Blob(x);}
};

Blob Blob::prototype;  // Calls up Factory<0>::insertInMap during compile time, but crashes.

int main()
{
    
}
