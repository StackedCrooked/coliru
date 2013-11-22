#include <iostream>
#include <utility>

struct Well {
};
Well const well {};

struct Bidon {
  Bidon() = default;
  Bidon( size_t capacity ) :
    capacity_ { capacity } {
  }

  friend Bidon& operator<<( Bidon & dest, Well const & ) {
    dest.Fill();
    return dest;
  }
  friend Bidon& operator>>( Bidon & dest, Well const & ) {
    dest.Empty();
    return dest;
  }

  friend Bidon& operator<<( Bidon & dest, Bidon & src ) {
    dest.FillFrom( src );
    return dest;
  }

  friend std::ostream& operator<<( std::ostream &os, Bidon const & bidon ) {
    os << "( " << bidon.quantity_ << " / " << bidon.capacity_ << " )";
    return os;
  }
private:
  size_t capacity_ { 5 };
  size_t quantity_ {};

  void FillFrom( Bidon & src ) {
    size_t maxIncome = capacity_ - quantity_;
    size_t income = std::min( maxIncome, src.quantity_ );
    quantity_ += income;
    src.quantity_ -= income;
  }
  void Fill() {
    quantity_ = capacity_;
  }
  void Empty() {
    quantity_ = 0;
  }
};

int main() {
  Bidon b5l;
  Bidon b3l { 3 };

  b5l << well; // bidon de 5l plein
  b3l << b5l; // bidon de 3l plein et bidon de 5l contient 2l
  b3l >> well; // bidon de 3l vide
  b3l << b5l; // bidon de 5l vide et bidon de 3l contient 2l
  b5l << well; // bidon de 5l plein
  b3l << b5l; // bidon de 3l plein et bidon de 5l contient 4l :)  

  std::cout << b5l << std::endl;
  return 0;
}