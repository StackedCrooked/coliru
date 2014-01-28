#include <type_traits>

struct concrete_class {

};

static_assert(std::is_abstract<concrete_class>(), "concrete_class ought to be abstract.");
