template<class T>
class Machin{ //j'aime pas les bananes
public:
  T& function(){
      static T objet;
      return objet;
  }
};

int main(){
    Machin<int> m;
    Machin<Machin<int>> mm;
    
    int& i = m.function();
    Machin<int> & rm = mm.function();
    
    return 0;
}