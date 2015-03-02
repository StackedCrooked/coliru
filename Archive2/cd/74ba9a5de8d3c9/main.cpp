#include <memory>
int main() {
    std::unique_ptr<int> up( new int( 30 ) );
}
