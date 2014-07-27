using max_align_t = double;

#include <memory>
#include <cstddef>

using std::unique_ptr;
using std::nullptr_t;

struct Job{};
struct FIFOSequencer{};

class int_ptr : public std::unique_ptr<int>
{
public:
    constexpr int_ptr()
        : std::unique_ptr<int>(), sequencer( nullptr ) {}
    constexpr int_ptr( nullptr_t )
        : std::unique_ptr<int>( nullptr ), sequencer( nullptr ) {}
private:
    int* sequencer;
};

int main()
{
    job_ptr x;
}