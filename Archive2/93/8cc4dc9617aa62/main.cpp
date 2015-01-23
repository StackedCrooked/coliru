struct A {};

int main()
{
    A[] pointersToA = A[3];
    pointersToA[0] = &B();
    pointersToA[1] = &C();
    pointersToA[2] = &D();
    
    return 0;
}