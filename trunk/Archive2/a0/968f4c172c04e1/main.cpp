
template<typename T,
typename F,
typename... Rest>
warp_base_class_helper
{
  using type = typename F<T typename warp_base_class_helper>::type;
}

int main()
{
}
