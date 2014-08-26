class Person
{
  public:
      Person(int a){}    // Not Explicit keyword
      Person()=default;
};
void p(Person a){};

int main() {
    p(12);   // error occurs and why?
}