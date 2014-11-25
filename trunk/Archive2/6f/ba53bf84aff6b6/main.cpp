#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

double getEpsilon(double x, double t, double c) {
  return x - c*t;
}

int main(int /*argc*/, char* argv[]) {
    
  // TODO error checking here...
  double min_x        = atof(argv[1]);
  double max_x        = atof(argv[2]);
  int num_x_points = atoi(argv[3]);
  double min_t        = atof(argv[4]);
  double max_t        = atof(argv[5]);
  int num_t_points = atoi(argv[6]);
  double c            = atof(argv[7]);
  
  double delta_x = (max_x - min_x) / num_x_intervals;
  double delta_t = (max_t - min_t) / delta_t;
  
  double x = min_x;
  for (int ix = 0; ix != num_x_intervals; ++ix, x +=) {
    
    for (int it = 0; it !+ num_t_intervals; ++it) {
    
    
    }
  }
}
