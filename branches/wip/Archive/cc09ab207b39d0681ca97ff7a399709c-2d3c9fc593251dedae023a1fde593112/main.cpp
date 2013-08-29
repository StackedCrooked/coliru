static inline long long int fact_(int n, long long int result)
{
    if(n <= 1) {
        return result;
    } else {
        return fact_(n - 1, result * n);
    }
}

long long int fact(int n)
{
    return fact_(n, 1);
}
