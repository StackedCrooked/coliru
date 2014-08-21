#include <iomanip>
#include <iostream>

// Utility for encoding floating point numbers in fixed point format.
// Does not do any overflow checking.
template <unsigned IntegerBits, unsigned FractionalBits>
class FixedPoint
{
public:
   FixedPoint(double d) { SetValue(d); }
   FixedPoint(float f) { SetValue(static_cast<double>(f)); }
   unsigned int IntValue() const { return mValue; }

private:
   void SetValue(double d)
   {
      const unsigned int factor = 1 << FractionalBits;
      
      bool was_negative = d < 0;
      if (was_negative) { d *= -1.0; }

      unsigned int integer = static_cast<unsigned int>(d);
      double frac = d - integer;
      
      frac *= factor;
      unsigned int result = static_cast<unsigned int>(frac);
      
      mValue = (integer << FractionalBits) | result;
      
      if (was_negative)
      {
         // 2s complement - invert and add 1
         mValue = ~mValue;
         mValue += 1;
      }
   }
   unsigned int mValue;
};

int main(int argc, char* argv[])
{
    std::cout << "8 INT, 8 FRAC,  1.3: 0x" << std::hex << FixedPoint<8, 8>(1.3).IntValue() << std::endl;
    std::cout << "8 INT, 8 FRAC, -1.3: 0x" << std::hex << FixedPoint<8, 8>(-1.3).IntValue() << std::endl;
    
    std::cout << "12 INT, 4 FRAC,  1.3: 0x" << std::hex << FixedPoint<12, 4>(1.3).IntValue() << std::endl;
    std::cout << "12 INT, 4 FRAC, -1.3: 0x" << std::hex << FixedPoint<12, 4>(-1.3).IntValue() << std::endl;
}
