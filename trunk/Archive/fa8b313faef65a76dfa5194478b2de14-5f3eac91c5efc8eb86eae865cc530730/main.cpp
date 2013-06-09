int (*my_array)[10]; // pointer to an array, not the actual array (just a pointer)

int (*function())[10] // this function returns a pointer
{
    return my_array; // the pointer now pointing to this object
}

int main()
{
    int (*arr)[10] = function(); // assign the pointer to arr
}