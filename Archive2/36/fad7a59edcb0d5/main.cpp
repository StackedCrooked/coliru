#include <iostream>
#include <cmath>

int main()
{
    size_t n_cases;
    std::cin.exceptions(std::ios::failbit);

    std::cin >> n_cases;
    for (size_t case_number = 1; case_number<= n_cases; ++case_number)
    {
        double r, ink;
        std::cin >> r >> ink;

        /*
         * First ring: width 1cm at radius [r,r+1)
         *
         * The area of the rings:
         *
         *   First ring:   pi(r+1)^2 - pi(r+0)^2
         *   Second:       pi(r+3)^2 - pi(r+2)^2
         *   Third:        pi(r+5)^2 - pi(r+4)^2
         * etc.
         *
         * So the amount of ink required for n rings is
         *
         *  ink = sum(k=0..n, (r+2k+1)^2-(r+2k)^2)
         *
         * Wolfram alpha gives the equivalence "sum (r+2k+1)^2-(r+2k)^2, k=0 to n"
         *
         *  ink = (n+1)*(2*n+2*r+1)
         *
         * So we can solve for n: "solve (n+1)*(2*n+2*r+1) = a for n" (a is "ink")
         *
         *       n = (sqrt(pi) sqrt(8 a+4 pi r^2-4 pi r+pi)-2 pi r-3 pi)/(4 pi) 
         *  ~~ 
         *       0.079577 (1.7725 sqrt(8.0000 a+12.566 r^2-12.566 r+3.1416)-6.2832 r-9.4248)
         */
        double n = (sqrt(8.*ink+4.*r*r-4.*r+1)-2.*r-3.)/(4.);

        std::cout << "Case #: " << case_number << ": " << long(n+1) << "\n";
    }
}
