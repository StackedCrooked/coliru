
struct Gadget { int value; };

template<typename T>
struct Widget
{
    static Gadget x;
};
template<typename T> Gadget Widget<T>::x;

struct Button
{
    static Gadget x;
};
Gadget Button::x;

int main()
{
    int x = Widget<int>::x.value;
}