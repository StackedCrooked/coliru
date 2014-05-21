#include <iostream>
#include <map>


int main() {
    /**
     * Generate triangles upto 2 * 10^6
     * deduce lower possibilities
     */
     
     /**
      * 2x1 = 3
      * 2x2 = 9
      * 2x3 = 18
      * 
      * 3x1 = 6
      * 3x2 = 18
      * 3x3 = 36
      * 3x4 = 52?54
      * 
      * 4x1 = 10
      * 4x2 = 30 
      * 
      * 5x1 = 15
      * 
      * 
      * 
      * startnumber = triangle[i]
      * n = triangle * ((3 + n) + n)
      */
     
    int solution = 0;
    const int limit = 2000000;
    
    std::map<int, int> seg;
    int newSum = 2;
    
    for (unsigned i1 = 1, 
        i2 = 0; 
        i1 < limit; 
        i1 += newSum, 
        i2++, 
        newSum++) {
        
        seg.insert( { i2, i1 });
    }
    
    std::cout << std::endl;
    std::cout.flush();
    int currHigh = 1000000;
    for (const auto& e : seg) {
        const int current = e.second;
        std::cout << "Testing: " << current << " ";
        
    
        int factor = 3;
        int oldResult = 0;
        
        for (int i = 1;; i++) {
            const int currResult = current * factor;
            
            //std::cout << ", ";
            
            if (currResult > limit) {
                const int first  = currResult - limit;
                const int second = limit - oldResult;
                
                if (first < currHigh) {
                    //std::cout << "New low(F): " << first << " with " << e.first << std::endl;
                    currHigh = first;
                    solution = (i * e.first);
                }
                
                if (second < currHigh) {
                    //std::cout << "New low(S): " << second << " with " << e.first << std::endl;
                    currHigh = second;
                    solution = (i * e.first);
                }
                
                break;
            }
            oldResult = currResult;
            factor += 3;
        }
        std::cout << std::endl;
    }
    
    
    
    
    std::cout << "Solution: " << solution << std::endl;
}