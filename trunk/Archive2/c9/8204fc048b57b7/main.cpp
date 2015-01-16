#include <iostream>
#include <vector>

class myClass {
public:
   std::vector<double> xpoint1, xpoint2, ypoint1, ypoint2;
   void foo(const std::vector<double> & px1, const std::vector<double> & px2, const std::vector<double> & py1,  const std::vector<double> & py2){
         xpoint1 = px1;
   }
};

int main() {
	myClass my_arr[2][10];
	my_arr[1][0].foo(std::vector<double>(), std::vector<double>(), std::vector<double>(), std::vector<double>());
	
	return 0;
}