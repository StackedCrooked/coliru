struct myStruct {int i; int j;};

myStruct myFunction(int myArg){
    switch (myArg) {
    case 0: return {1,2};
    case 1: return {2,3};
    default: return {4,5};
    }
}

int main()
{
}