int main() {
  int i = 0;
  decltype(auto) c = ({ i++; 0; });
  (void)c;
}