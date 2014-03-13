#include <iostream>


struct PrivateMember
{
private:
    int a;
    char b;
};

struct PublicMember
{
    int a;
    char b;
};

struct ExtendMember
{
    PrivateMember a;
    char b;
};

struct ExtendManual
{
    int a;
    char b;
    char c;
};

struct DerivePrivateMember:PrivateMember
{
    char c;
};

struct DerivePublicMember:PublicMember
{
    char c;
};


#define SHOW_SIZE(name) \
std::cout << #name << ": " << sizeof(name) << std::endl;

int main(int argc, char** argv) {
    SHOW_SIZE(PrivateMember);
    SHOW_SIZE(PublicMember);
    SHOW_SIZE(ExtendMember);
    SHOW_SIZE(ExtendManual);
    SHOW_SIZE(DerivePrivateMember);
    SHOW_SIZE(DerivePublicMember);
    return 0;
}