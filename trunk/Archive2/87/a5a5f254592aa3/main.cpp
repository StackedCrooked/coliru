#include <stdio.h>

void i_know_my_name(void)
{
    printf("%s\n", __func__);
}

int main(void)
{
    i_know_my_name();
    printf("%s\n", __func__);
}