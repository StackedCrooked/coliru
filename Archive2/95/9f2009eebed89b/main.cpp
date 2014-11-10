enum round_mode { round_half_up, round_half_down, round_bankers };

double round( double , round_mode = round_half_up ) ;

int main()
{
  round( 2.5, 42 ); // *** error: no implicit conversion from 'int' to 'round_mode'
}
