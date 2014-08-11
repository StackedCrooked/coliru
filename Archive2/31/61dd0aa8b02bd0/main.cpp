#include <utility>

namespace foo
{
    struct MoveOnly{
        MoveOnly() = default;
        ~MoveOnly() = default;
        
        MoveOnly(MoveOnly const &) = delete;
        MoveOnly & operator=(MoveOnly const &) = delete;
        
        MoveOnly(MoveOnly &&) = default;
        MoveOnly & operator=(MoveOnly &&) = default;
    };
    
    struct CopyOnly{
        CopyOnly() = default;
        ~CopyOnly() = default;
        
        CopyOnly(CopyOnly const &) = default;
        CopyOnly & operator=(CopyOnly const &) = default;
        
        CopyOnly(CopyOnly &&) = delete;
        CopyOnly & operator=(CopyOnly &&) = delete;
    };
    
    struct ExpectMovable: MoveOnly, CopyOnly{};
}
int main()
{
    foo::ExpectMovable tmp;
    foo::ExpectMovable newLocation = std::move(tmp);
}
