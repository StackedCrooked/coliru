template <int n> class BigInt {
public:
  BigInt() {}
  template <int m> BigInt(const BigInt<m>&) {}
  BigInt operator+(const BigInt&) { return BigInt(); }
};

int main()
{
  BigInt<8> a;
  BigInt<6> b;
  BigInt<8> c = a+b;
  return 0;
}