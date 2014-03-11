auto foo(int i) {
  if( i != 1 )
    return i;
  else 
    return foo(i-1)+i ; 
}

int main()
{
}