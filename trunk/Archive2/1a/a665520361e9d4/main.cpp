#include <memory>

class T{};

int main(){
    std::shared_ptr<const T> t = std::make_shared<T>();
}
