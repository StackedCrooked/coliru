int main()
{
    int out_array[5] = {};
    int mx_array[5] = {};
    int *out_array_ptr = &out_array[0];
    int *mx_array_ptr = &mx_array[0];
    
    out_array_ptr = mx_array_ptr;
}
