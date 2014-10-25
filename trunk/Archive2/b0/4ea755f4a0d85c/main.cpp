template<typename T>
class A
{ };

int main()
{
    A<float> a(A<float>::A<int>());
    return 0;
}