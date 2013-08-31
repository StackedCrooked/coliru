int (*my_array)[10];

int (*function())[10]
{
    return my_array;
}

int main()
{
    int (*arr)[10] = function();
}