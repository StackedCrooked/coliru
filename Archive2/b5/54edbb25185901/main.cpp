#include <iostream>
#include <memory>
 
class Widget {
public:
    Widget() {}
    Widget(int, int) { }
private:
    Widget(const Widget& ) = delete;
    void operator=(const Widget &) = delete;
};
 
int main() {
    const std::size_t number_of_widgets = 2;
	std::array<Widget, number_of_widgets> w;
    for (int i = 0; i < 2; ++i) {
        w[i] = Widget(i, i);
    }
	return 0;
}
 