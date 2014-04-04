#include <memory>

int main() {
    std::shared_ptr<int> node;

    // later on:
    const auto hook = [=, slave = std::weak_ptr<int>(node)]()
    {
      if (!slave.expired())
        ;//do something
      else
        ;// do nothing; the class has been destroyed!
    };   
}