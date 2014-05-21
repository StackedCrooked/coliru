struct Letter {
    enum LetterEnum {LetterA, LetterB, LetterC, LetterCount};
    
    virtual void foo() = 0;
  
    static std::unique_ptr<Letter> construct(LetterEnum c);
};

struct A : Letter {
  A(int n, bool b, char const *name);
  void foo() override;
};

struct B : Letter {
  B(int n, bool b, char const *name);
  void foo() override;
};

struct C : Letter {
  C(double d);
  void foo() override;
};









std::unique_ptr<Letter> Letter::construct(LetterEnum c) 
{
    switch(c) {
    case Letter::LetterA : return make_unique<A>();
    case Letter::LetterB : return make_unique<B>();
    case Letter::LetterC : return make_unique<C>();
    default: throw ...;
    }
}

int main() {
    char c;
    std::cin >> c;
    //get a letter of the derived type associated with the letter entered
    std::unique_ptr<Letter> ptr = Letter::construct(c);    
}