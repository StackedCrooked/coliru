class A{
    public:

    explicit operator int() const{
        return 2;
    }
};

int main() {
  A a;
  return 0;
};