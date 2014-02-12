

union{
    __m256d align;
    char A[sizeof(ChildClassA)];
    char B[sizeof(ChildClassB)];
    char C[sizeof(ChildClassC)];
};

ParentClass *ptr;

switch (...){
case 0:
    ptr = new (&A) ChildClassA();
case 1:
    ptr = new (&B) ChildClassB();
case 2:
    ptr = new (&C) ChildClassC();
}

ptr->method1();
ptr->method2();
ptr->method3();