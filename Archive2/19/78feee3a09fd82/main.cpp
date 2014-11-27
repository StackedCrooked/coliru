struct X
{
  X(int i) { i = i; }
  int i;
};

int main() {    
    X x(42);
    return 0;
}