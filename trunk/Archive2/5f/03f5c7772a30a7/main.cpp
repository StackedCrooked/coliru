#include <stdint.h>

struct PointerData
{
    union
    {
        struct
        {
            bool _invalid       :1;
            bool _delete        :1;
            bool _unused        :1;
            uint64_t _pointer   :29;
        } _s;
        uint32_t _i;
    };

    constexpr PointerData(bool invalid, bool isDelete, bool unused)
        : _s { invalid
        , isDelete
        , unused
        , 0 }
    {
    }
};
static_assert(PointerData(true, false, false)._i == 1, "PointerData not supported");
static_assert(PointerData(false, true, false)._i == 2, "PointerData not supported");
static_assert(PointerData(false, false, true)._i == 4, "PointerData not supported");
