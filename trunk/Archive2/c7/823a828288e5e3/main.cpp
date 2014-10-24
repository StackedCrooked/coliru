#include "Bitmask.h"
#include <iostream>

  const BitMask MASK_ONE   = ( ( std::cout << "initialise MASK_ONE\n" ), BitMask(1) ) ;
  const BitMask MASK_TWO   = ( ( std::cout << "initialise MASK_TWO\n" ), BitMask( 1 << 1 ) ) ;
  const BitMask MASK_THREE = ( ( std::cout << "initialise MASK_THREE\n" ), BitMask( 1 << 2 ) ) ;
  