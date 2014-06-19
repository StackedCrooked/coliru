    #include<iostream>
    
    namespace mymath {
      long long int sqrt(long long int a) {
        long long int upper = a;
        long long int lower = 0;
        long long int  mid  = a;

        while (!(mid * mid >= a && (mid - 1) * (mid - 1) < a)) {
          mid = (lower + upper) / 2;
          if (mid * mid > a){
            upper = mid;
          } else if (mid * mid <= a){
            lower = mid;
          }
        }
        return mid;
      }
    }
    
    int main(){
      std::cout << mymath::sqrt(10) << std::endl;
    }