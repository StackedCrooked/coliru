class X
{
  int i;
};

X fun()
{
 return X();
}
void func(X &x)
{

}

int main()
{

 func(fun());
 return 0;
}