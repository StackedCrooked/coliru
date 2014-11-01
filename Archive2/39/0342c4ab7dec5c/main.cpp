namespace N { 
  struct A { 
    friend struct B;

    void func (); 

    private:
      int _data;
  };  
}

struct B { 
  void access (N::A& x) {
    x._data = 1; // error: private
  }
};

namespace N { 
  void A::func () {
    B x; x.access (*this);
  }
}

int main () {
  // ...
}