constexpr const int A = 42;

const int &B = A;
static_assert(&A == &B, "Bug");

constexpr const int &C = B;
static_assert(&A == &C, "Bug");


int main()
{
}