class Bar{
public:
  Bar(int, int, int);
};

int main () {
  int x = 1;
  Bar bar(int(x), int(x), int{x});
}