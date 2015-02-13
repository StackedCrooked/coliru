auto Wrong(auto i) {
  if (i != 1)
    return Wrong(i-1)+i;  // Too soon to call this. No prior return statement.
  else
    return i;             // return type deduced as int
}

int main() {
    Wrong(1);
    return 0;
}