#include <iostream>

namespace jesseb303 
{
    class statistician
    {
    public:
        // CONSTRUCTOR
        statistician( );
        // MODIFICATION MEMBER FUNCTIONS
        void next(double r);
        void reset( );
        // CONSTANT MEMBER FUNCTIONS
        int length( ) const;
        double sum( ) const;
        double mean( ) const;
        double minimum( ) const;
        double maximum( ) const;
        // FRIEND FUNCTIONS
        friend statistician operator + (const statistician& s1, const statistician& s2);
        friend statistician operator * (const statistician& s1, const statistician& s2);
        friend bool operator ==(const statistician& s1, const statistician& s2);
   
    private:
        int count;       // How many numbers in the sequence
        double total;    // The sum of all the numbers in the sequence
        double tinyest;  // The smallest number in the sequence
        double largest;  // The largest number in the sequence
    };

   
   
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

namespace jesseb303
{
   statistician::statistician() : count(0), total(0), tinyest(0), largest(0)
   {}                                          //initializing everything to 0
 
   /*-----------------------------------------------------------------------+
   | next(double r)
   |
   | Give the statistician a new number
   |
   | Post: the count of the numbers statistician has seen has been
   |    incremented
   |       the sum of all the numbers statistician has seen has been
   |    increment by r
   |       the values of tinyest and largest have been adjusted if
   |    necessary
   */
   void statistician::next(double r)
   {
       if (count <= 0) {                       // update the number of entries statistician has
           count = 1;                          // this is the first data item of the statistician
           total = r;
           tinyest = r;
           largest = r;
           return;
       }
       count += 1;
       total += r;                             // adjust the sum
       if (r < tinyest) {                      // update the min if necessary
           tinyest = r;
       }
       if (largest < r) {                      // update the max if necessary
           largest = r;
       }
   }
 
   void statistician::reset( )
   {
       count = 0;                              // resets all values back to 0
       tinyest = 0;
       largest = 0;
       total = 0;
   }
 
       /*-------------------------------------------------------------------+
       | int length( ) const
       |
       | RETURN count which is the length of the sequence that has
       |    been given to the statistician (i.e., the number of times that the
       |    next(r) function has been activated).
       */
   int statistician::length() const
   {
       return count;
   }
 
   double statistician::sum() const
   {
       return total;
   }
 
   double statistician::mean() const
   {
       return total/count;                     // mean = total divided by the number of numbers
   }
 
   double statistician::minimum() const
   {                                           // minimum = tinyest number
       return tinyest;
   }
 
   double statistician::maximum() const
   {
       return largest;                         // maximum = largest number
   }
 
   bool operator ==(const statistician& s1, const statistician& s2)
   {
       if (s1.length()==s2.length())
    {
    return (1);
    }
    else 
    return (0);
   }
 
   statistician operator + (const statistician & s1, const statistician & s2)
   {
       statistician s3;
       s3.next(s1.sum() + s2.sum());
       return s3;
   }
 
   statistician operator * (const statistician& s1, const statistician& s2)
   {
      statistician s3;
        s3.next(s1.sum() * s2.sum());
       return s3;
   }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    jesseb303::statistician a, b ;
    a.next(123.45) ; a.next(56.78) ;
    b.next(90.12) ; b.next(34.56) ;
    
    std::cout << (a+b).sum() << ' ' << (123.45+56.78)+(90.12+34.56) << '\n'
              << (a*b).sum() << ' ' << (123.45+56.78)*(90.12+34.56) << '\n' ;
}
