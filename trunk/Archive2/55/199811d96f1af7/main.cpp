struct NonStack
{
private:
  NonStack() = default;
public:
  static NonStack* Create(){
    return new NonStack;
  }
};

int main()
{
    NonStack a;
}
