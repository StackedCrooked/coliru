long long int fact(int n)
{
    static long long int result = 1;

    if(n <= 1) {
        long long int temp = result;
        result = 1;
        return temp;
    } else {
        result *= n;
        return fact(n - 1);
    }
}
