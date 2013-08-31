#include <memory>
#include <functional>

int main() {
    auto fn = std::bind<void*>(operator new[], sizeof(char)*100);

    auto field = (char*)fn();
}