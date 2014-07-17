#include <vector>
#include <algorithm>

template <int dimention, typename type>   
class Point{
public:
    Point() {mCoords = new type[dimention];}
    int getDimention() const {return dimention;}
    type& at(int i) {return mCoords[i];}
    const type& at(int i) const {return mCoords[i];}

private:
    type* mCoords;
};

struct lexCompPoints {
    //comparitors emulate `operator<`
    template <int dimention, typename type>  
    bool operator()(const Point<dimention,type>& left, const Point<dimention,type>& right)
    {
        //see how many points they share
        int end = std::min(left.getDimention(), right.getDimention());
        //the first point that differs determines the comparison
        for(int i=0; i<end; ++i) {
            if (left.at(i) != right.at(i))
                return left.at(i) < right.at(i);
        }
        //if one is a lower dimension, that determines the comparison
        if (left.getDimention() != right.getDimention())
            return left.getDimention() < right.getDimention();
        //otherwise they're equal
        return false;
    }
};

int main() {
    //get data
    std::vector<Point<3,float>> data(4);
    
    //sort it
    std::sort(data.begin(), data.end(), lexCompPoints{});    
    
    //if Point had an `friend bool operator<(const Point& left, const Point& right) then:
    //std::sort(data.begin(), data.end());
}