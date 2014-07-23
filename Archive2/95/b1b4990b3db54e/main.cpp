#include <type_traits>

class BaseT {};
class BaseU {};
class BaseV {};

class DerivedT : public BaseT {};
class DerivedU : public BaseU {};
class DerivedV : public BaseV {};

template < class Td, class Ud, class Vd, class Enable = void>
class Extractor;

template <class Td, class Ud, class Vd>
class Extractor<Td, Ud, Vd, typename std::enable_if<std::is_base_of<BaseT, Td>::value && std::is_base_of<BaseU, Ud>::value && std::is_base_of<BaseV, Vd>::value>::type> {

};

int main() {
  Extractor<DerivedT, DerivedU, DerivedV> dummy;
}