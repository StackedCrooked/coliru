struct myStruct {int i; int j;};

myStruct myFunction(int myArg){
    switch (myArg) {
    case 0: return (struct myStruct){1,2};
    case 1: return (struct myStruct){2,3};
    default: return (struct myStruct){4,5};
    }
}

int main()
{
}