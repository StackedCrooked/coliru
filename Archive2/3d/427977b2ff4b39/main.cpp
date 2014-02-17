class threestack
{
    int stacksize = 100;
    int* buffer;
    int stackpointer[3]= {-1, -1, -1};
public:
    threestack(int stacksize_u)
    {
        int buffer_u[stacksize_u*3];
        this->buffer = buffer_u;
        this->stacksize = stacksize_u;
    }
    threestack()
    {
        int buffer_u[(this->stacksize)*3];
        this->buffer = buffer_u;
    }

    bool push(int stacknum, int value);
    bool pop(int stacknum);
    int peek(int stacknum);
    bool empty(int stacknum);
};

int main() {}