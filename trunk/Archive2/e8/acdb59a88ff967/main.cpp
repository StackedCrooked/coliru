int arr[2];

int (*ptr)[2] = (int (*)[2]) &arr[1];

int main()
{
    ptr[0][1] = 0;
}