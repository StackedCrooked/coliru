#include <cstddef>
#include <type_traits>

namespace oslash {
    struct type;

    struct object {
        type* isa;
    };

    static_assert(std::is_standard_layout<object>(), "Not standard layout");
    static_assert(offsetof(object, isa) == 0, "Offset is incorrect");

    struct method {
        using selector = char*;
        using implementation = object*(*)(object*, selector, ...);

        selector sel;
        implementation impl;
    };

    static_assert(std::is_standard_layout<method>(), "Not standard layout");
    static_assert(offsetof(method, sel) == 0, "Offset is incorrect");
    static_assert(offsetof(method, impl) == 8, "Offset is incorrect");

    struct type : object {
        method *methods;
        char **data_members;
        char *name;
    };

    static_assert(std::is_standard_layout<type>(), "Not standard layout");
    static_assert(offsetof(type, isa) == 0, "Offset is incorrect");
    static_assert(offsetof(type, methods) == 8, "Offset is incorrect");
}
