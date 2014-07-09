    #include <type_traits>
    
    class fileUnstructuredView {
    private:
        void* view;
    public:
        template<class T, 
            class enabled=typename std::enable_if<std::is_pod<T>::value>::type
            >
        operator T*() {
            return view;
        }
    };
    struct a { };
    
    #include <string>
    
    int main() {
        fileUnstructuredView p;
        int* i = p;
        a* b = p;
        std::string* s = p;
    }