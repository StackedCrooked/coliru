

struct ABC
{
    int a, b, c;
};


void foo(ABC) {}


int main(int argc, char** argv)
{
    
    ABC abc;
    ABC def = abc;
    
    foo(def);
}