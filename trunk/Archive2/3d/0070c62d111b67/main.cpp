class A
{
    public:
    typedef enum A_ENUMS { NONE, ALL } A_ENUMS;
};

struct ASettings
{
    A::A_ENUMS myASetting;
};

int main()
{}