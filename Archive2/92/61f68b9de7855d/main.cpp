constexpr bool isPrime(int value) {
  if(value < 2)
    return false;
        
  int divisor;
  for(divisor = 2;
     (divisor*divisor <= value) && (value % divisor);
     ++divisor);
  return (divisor*divisor > value);
}

int main() {
    
}