//a user defined type
class Widget{};

//a function that takes a Widget
void function (Widget w){}
//inherit instead

class Gadget: Widget { using Widget::Widget; };

int main(){

    //make a typedef (this is C++11 syntax for a typedef. It's the same thing)
    //using Gadget = Widget;

    //make the two "different types" (well.. they're not really different as you will see)
    Widget w;
    Gadget g;

    //call a function that should ONLY accept Widgets
    function(w); //works (good)
    function(g); //<- works (I do not want this to compile though)

}
