#include <memory>

int main(int, char*[]) {
    std::unique_ptr<int> x ( new int(1) );
    std::unique_ptr<int> y = new int(1);
    return 0;
}