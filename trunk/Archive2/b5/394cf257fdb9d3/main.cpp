class Outter {
  public:
    class Inner {
      //priv members & pub functions
    };

  private:
    Inner * inner_ptr; 
};

class Third {
  public:
    Outter* someFunc();
    Outter::Inner* anotherFunc();
};

int main() {
}