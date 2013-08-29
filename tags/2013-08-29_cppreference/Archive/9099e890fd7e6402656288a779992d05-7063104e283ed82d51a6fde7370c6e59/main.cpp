#pragma once
#include <string>
#include <vector>

namespace oslash {
    struct object;
    
    struct type {
        std::string name;
        std::vector<std::string> member_names;
    };
}

static_assert(std::is_standard_layout<oslash::type>::value,
              "oslash::type must be a standard layout type.");
