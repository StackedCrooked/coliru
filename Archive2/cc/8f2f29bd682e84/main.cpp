#include <iostream>
#include <memory>

class Model {
    friend class Window;
public:
    int i = 1337;
private:
    Model();
};

class Window {
public:
    std::shared_ptr<Model> get_model() {return std::make_shared<Model>();}
};


int main() {
    Window win;
    auto model = win.get_model();
    std::cout << "model i: " << model->i << std::endl;
}