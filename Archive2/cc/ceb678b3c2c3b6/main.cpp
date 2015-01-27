template <typename> struct custom_copy_ctor {
  template <typename... Ts> custom_copy_ctor(Ts...) {}
  custom_copy_ctor(custom_copy_ctor const &) {}
  // custom_copy_ctor(custom_copy_ctor const&) = default; // works fine
};

int main() {
  custom_copy_ctor<void> cc;
  [cc](auto) {}(1);
  //[cc](int){}(1); // works fine
  return 0;
}