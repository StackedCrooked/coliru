class FirstClass
{
public:
  virtual ~FirstClass(void);

  virtual void Foo() = 0;
  virtual void Bar() = 0;
};

class SecondClass  : public FirstClass
{
public:
     SecondClass();
virtual ~SecondClass(void);

void Foo();
void Bar();

};

SecondClass::SecondClass() {}
SecondClass::~SecondClass(void) {}
void SecondClass::Foo() {}
void SecondClass::Bar() {}

int main()
{
        SecondClass m;
}