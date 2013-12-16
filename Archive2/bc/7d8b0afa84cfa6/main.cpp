unsigned long long factorial(unsigned long long n) {
  if (n <= 1) return 1;
  else return n * factorial(n-1);
}
