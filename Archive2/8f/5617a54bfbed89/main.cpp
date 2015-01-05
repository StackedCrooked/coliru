void foo(int *a);
void foo(int a[]); //OK, redeclrartion

int *a;
int a[]; //error, a has been already declared as a pointer

int main(){ }