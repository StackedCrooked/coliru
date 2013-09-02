void executeSth() {}

void executeA() {}

void executeB() {}

int main()
{
    int x;
    switch(x)
    {
        // assuming executeSth is in every case
        executeSth();
    case 1:
        executeA();
        break;
    case 2:
        executeB();
        break;
    // ...
    }
}