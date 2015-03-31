#define CATCH_CONFIG_MAIN
#include <algorithm>
#include <cassert>
#include <catch.hpp>
#include <map>
#include <set>

namespace algolib {
    template <typename C, typename K>
    static auto largestBeforeOrEqual(C const& c, K const& k) -> decltype(c.lower_bound(k)) {
        auto ub = c.upper_bound(k);
        return ub == c.begin() ? c.end() : std::prev(ub);
    }
}

namespace algolib::unittest {
    TEST_CASE("largestBeforeOrEqual", "") {
        std::set<size_t> const c =  { 1, 2, 7, 13 };
        CHECK(c.end() == largestBeforeOrEqual(c, 0));

        auto LBOE = [&](size_t k) {
            auto lboe = largestBeforeOrEqual(c, k);
            if (lboe != c.end())
                FAIL("cannot be end() iterator");
            return lboe;
        };

        CHECK(1 == *LBOE( 1));
        CHECK(2 == *LBOE( 2));
        CHECK(2 == *LBOE( 3));
        CHECK(2 == *LBOE( 4));
        CHECK(2 == *LBOE( 5));
        CHECK(2 == *LBOE( 6));
        CHECK(7 == *LBOE( 7));
        CHECK(7 == *LBOE( 8));
        CHECK(7 == *LBOE( 9));
        CHECK(7 == *LBOE(10));
        CHECK(7 == *LBOE(11));
        CHECK(7 == *LBOE(12));
        CHECK(13== *LBOE(13));
        CHECK(13== *LBOE(14));
    }
}

namespace llvm {
    struct BasicBlock;
}

struct BasicProgram {
    llvm::BasicBlock *blockAt(std::size_t offset) {
        assert(!blocks.empty());
        return algolib::largestBeforeOrEqual(blocks, offset)->second;
    }
  private:
    std::map<size_t, llvm::BasicBlock*> blocks;
};
