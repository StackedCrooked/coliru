class Factory
{
public:
    template<typename ...Args>
    static void testFunc(Args&& ...) { }
};

int main() {
    void(*pFunc)() = &Factory::testFunc;
}