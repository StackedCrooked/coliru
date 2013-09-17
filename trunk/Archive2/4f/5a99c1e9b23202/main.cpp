#include <unordered_map>
#include <algorithm>
#include <memory>
#include <vector>
#include <cassert>

template <typename K, typename V>
using hash_map = std::unordered_map<K,V>;

struct X{};

int main()
{

    std::vector<std::unique_ptr<X>> uniq_ptrs;
    std::vector<const X*> const_ptrs;

    // naive approach, no performance worries
    auto idx_of = [&](X const* p) {
        return std::distance(begin(const_ptrs), std::find(begin(const_ptrs), end(const_ptrs), p)); 
    };
    std::sort(begin(uniq_ptrs), end(uniq_ptrs), [&](std::unique_ptr<X> const& a, std::unique_ptr<X> const& b) {
                return idx_of(a.get()) < idx_of(b.get());
            });

    // less naive approach, no performance worries
    hash_map<const X*, int> indices;
    for (auto i = 0u; i < const_ptrs.size(); ++i) {
        indices[const_ptrs[i]] = i;
    }

    std::sort(begin(uniq_ptrs), end(uniq_ptrs), [&](std::unique_ptr<X> const& a, std::unique_ptr<X> const& b) {
                return indices[ a.get() ] < indices[ b.get() ];
            });

#if 0
    // cheating! only when `const_ptrs` can be made `non-const`
    assert(const_ptrs.size() == uniq_ptrs.size());
    for (auto i = 0u; i < const_ptrs.size(); ++i) {
        uniq_ptrs[i].release();
        uniq_ptrs[i].reset(const_ptrs[i]);
    }
#endif
}
