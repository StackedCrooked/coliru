int main() {
  int *p = new int;
  if(!p) return 1024;
  return *p;
}