template <typename T>
class A {
public:
    A() {}
    ~A() {
        static_assert(sizeof(T) > 0, "T is incomplete.");
    }
};

class B
{
public:
    B();
    ~B();

private:
    class impl;
    A<impl> m_impl{};
};

int main()
{
}