#include <iostream>
#include <cstring>
#include <type_traits>

static_assert(std::is_same<decltype((const int[10]){ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }),const int[10]>::value, "const int[10]");
static_assert(std::is_same<decltype((const int[10]){ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }),const int(&)[10]>::value, "const int(&)[10]");

using foo = const int[10];
static_assert(std::is_same<decltype(foo{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }),const int[10]>::value, "foo{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }");

template <typename T>
using Identity = T;
static_assert(std::is_same<decltype(Identity<const int[10]>{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }),const int[10]>::value, "Identity<const int[10]>{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 }");

static_assert(std::is_same<decltype(Identity<int>{42}),int>::value, "Identity<int>{42}");
