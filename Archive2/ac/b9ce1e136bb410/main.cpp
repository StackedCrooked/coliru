#include <iostream>

typedef unsigned tag_t;

template <tag_t>
struct TagTraits {};

template <tag_t TagId>
struct TagBinder {
  typedef TagTraits<TagId> Trait;

  enum { my_id = TagId };

  typename Trait::value_type item;
};

const tag_t IntTag = 100;
const tag_t BoolTag = 101;

template <> struct TagTraits<IntTag> {
  typedef int value_type;
};

template <> struct TagTraits<BoolTag> {
  typedef bool value_type;
};

int main() {
  TagBinder<IntTag> int_binder = TagBinder<IntTag>();
  return int_binder.item;
}
