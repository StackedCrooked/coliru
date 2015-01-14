template <typename T>
void f(T i)
{
g(i);
}
void g(int)
{
f(42);
}
int main(int argc, char* argv[])
{
return 0;
}