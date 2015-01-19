class A
{
public:
   A(const A&) : a(a) {}
private:
   int a;
};

int main() {}
