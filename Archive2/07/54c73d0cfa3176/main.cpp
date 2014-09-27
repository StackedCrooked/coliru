#include <unordered_set>
#include <memory>

typedef int Policy;
std::unordered_set<Policy> _policies;
std::shared_ptr<Policy> calculatePolicy() {
    return std::shared_ptr<Policy>(new int(42));
}


int main() {
    if ( std::shared_ptr<Policy> policy = calculatePolicy() )
    {
        auto res = _policies.insert ( *policy );
        if ( res.second )
            auto x = std::make_shared<Policy>( *res.first );
    }
}