#define MACRO {

#define END_1 };
#define END_2 END_1 };
#define END_3 END_2 };

#define END(x) END_ ## x

int main()
{
    MACRO
    MACRO
    MACRO
    END(3)
}