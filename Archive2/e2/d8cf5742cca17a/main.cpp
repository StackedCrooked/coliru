template<typename T>
struct S {
public:
    (*operator T() const)(int, int) { return nullptr; }
}; 
