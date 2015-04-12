#include <iostream>
#include <memory>
 
class Widget {
public:
    Widget(int, int) { }
};
 
int main() {
	const std::size_t number_of_widgets = 2;
	std::unique_ptr<Widget[]> widget(new Widget[number_of_widgets]{Widget(1, 2), Widget(3, 4)});
 
	return 0;
}
 