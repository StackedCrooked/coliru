template<typename T>
struct Bla
{
  using value_type = T;
};

template<typename T>
class Bla_no_cruft
{
};

template<typename T, typename U = void>
class Bla_more_args
{
};

template<typename T>
void f(const T& t)
{
  typename T::value_type some_var_of_template_type;
}

template<template<typename> class Class, typename T>
void f_no_cruft(const Class<T>& t)
{
  T some_var_of_template_type;
}

template<template<typename, typename...> class Class, typename T, typename... ArgTypes>
void f_more_args(const Class<T, ArgTypes...>& t)
{
  T some_var_of_template_type;
}

int main()
{
  f(Bla<int>());
  f_no_cruft(Bla_no_cruft<int>());
  f_more_args(Bla_more_args<int>());
}