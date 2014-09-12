class Object {
public:
    template <typename T>
    operator T() {
        std::cout << typeid(T).name() << std::endl;
        return T();
    }
};

class SomeClass {
};

int main(int argc, char *[]) {
    Object obj;
    char ch = obj;
    int i = obj;
    SomeClass s = obj;
    std::vector<int> vec = obj;
    std::string str = obj;
    return 0;
}