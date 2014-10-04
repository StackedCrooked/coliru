#include <iostream>

struct Foo { };
struct Bar { };

struct Builder {
  Foo foo_;
  Bar bar_;
  
  Builder() : foo_(), bar_() { }
  void doSomeBuilding() { /* Build Foo and Bar in some way... */ }
  
  Foo&& a_func_that_may_throw() { 
    // If something bad happens throw...
   
    // Steal built Foo from Builder.
    return std::move(foo_); 
  }
  Bar&& another_func_that_may_throw() {
    // If something bad happens throw...
    
    // Steal built Bar from Builder.  
    return std::move(bar_); 
  }
};

struct Widget {
  Foo foo_;
  Bar bar_;
  Widget() : foo_(), bar_() {}  // Construct empty Widget.
  Widget(Foo&& foo, Bar&& bar) : foo_(std::move(foo)),
    bar_(std::move(bar)) {} // Construct Widget with pre-built Foo and Bar. 
  void doSomething() {/* do something with foo_ and bar_ */}
};

Widget createWidget() {
  Builder builder; 
  builder.doSomeBuilding();    
  try {    
    Foo&& foo = builder.a_func_that_may_throw(); 
  } catch (const std::exception& e) {
    // Log that we can't get a Foo and deal with it...
    return Widget(); 
  }
  
  try {
    Bar&& bar = builder.another_func_that_may_throw();
  } catch (const std::exception& e) {
    // Log that we can't get a Bar and deal with it...
    return Widget();
  }
  return Bar(std::move(foo), std::move(bar)); // Want to use rvalue references here but can't!
}

int main() {
  auto widget = createWidget();
}
