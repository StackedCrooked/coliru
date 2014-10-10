int main () {
  void **v_dptr(nullptr);
  int  **i_dptr = static_cast<int**>(v_dptr);
  (void) i_dptr;
}