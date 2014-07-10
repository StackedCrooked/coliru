struct B{};
int f()
{ return 1;
}

int main()
{
      const int &i = f();
      int && j = f();
}