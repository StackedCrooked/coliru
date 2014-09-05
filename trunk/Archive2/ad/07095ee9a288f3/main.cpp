struct A
{
   A() = delete;
   A(int first, int second) {}
};
int main()
{
   new A[1] {{1, 2}};
}