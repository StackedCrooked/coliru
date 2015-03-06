#include <iostream>

class Context {
  public:
    Context& context() { return *this; }
    Context& context(Context& context) { return context; }
};

int main()
{
    Context context;
    context.context(context.context(context.context()));

    std::cout << "Done.\n";
}