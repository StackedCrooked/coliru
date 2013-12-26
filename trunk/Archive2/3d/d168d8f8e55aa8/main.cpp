int main() try {
  int *p = new int();
  if(!p) return 1024;
  return *p;
} catch (...) {
    return 1;
}
