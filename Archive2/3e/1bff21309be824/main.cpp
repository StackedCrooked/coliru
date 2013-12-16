struct T1 {};

typedef T1& T2;

int main()
{
    T1 x;
    T2& t = x;
}