struct X
{
    int inner_data_1 [3];
    int inner_data_2 [4];
};

template <typename T, unsigned N>
void bar (int (T ::* arg1) [N], int (& arg2) [N])
{
    // In the example below:
    //    arg1 should be a pointer to X::inner_data_X
    //    arg2[i] should be the value of outer_data_X[i]
    // and ultimately I want a pointer to X::inner_data_X[i]
}

int main ()
{
    X x;

    int outer_data_1 [3];
    int outer_data_2 [4];

    bar (& X::inner_data_1, outer_data_1);
    bar (& X::inner_data_2, outer_data_2);

    // This should create a compile error because N is mismatched
    //bar (& X::inner_data_1, outer_data_2);
}