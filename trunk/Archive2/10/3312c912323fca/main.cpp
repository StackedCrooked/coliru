#include <boost/scoped_ptr.hpp>
#include <iostream>

class Widget;
Widget *make_widget();

int main()
{  
  boost::scoped_ptr<Widget> sp(make_widget());
  std::cout << sizeof(Widget) << std::endl;
}

class Widget
{
public:
  Widget() {}
  ~Widget() { std::cout << "Widget destructor called." << std::endl; }
};

Widget *make_widget()
{
  return new Widget;
}
