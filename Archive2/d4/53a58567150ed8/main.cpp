enum MyEnum : int {};

int main()
{
  MyEnum me;

  int iv = static_cast<int>(me); // works
  int* ip = static_cast<int*>(&me); // "invalid static_cast"
}