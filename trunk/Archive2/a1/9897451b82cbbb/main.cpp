#include <memory>

int main()
{
    std::unique_ptr<int> pi(new int(42));
    
    auto ll = [ capturedInt = std::move(pi) ] () mutable { };
}