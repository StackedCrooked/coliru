#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include <algorithm>

/**
  * @brief simple point class of type T
  */ 
template <class T>
class point
{
public:
    point() {}
    virtual ~point() {}
    
    inline const T& x() const {return data[0];}
    inline const T& y() const {return data[1];}
    inline const T& z() const {return data[2];}
    
    inline T& x() {return data[0];}
    inline T& y() {return data[1];}
    inline T& z() {return data[2];}

private:
    T data[3];
};

/** @brief templated class that provides kd-tree functionality by sorting a vector
  * k-d trees are a good way to find the nearest point but trees aren't necessarily
  * efficient for hard storage. However, the functionality of a k-d tree can be
  * reproduced with a sorted vector which is efficient for storage
  */
template <class T>
class kdVector
{
public:
    
    kdVector() : sorted(false) {}
    virtual ~kdVector() {}
    
    /** 
      * @brief add a new point to the cloud
      */ 
    void addPoint(const point<T>& pnt)
    {
        sorted = false;
        kdVec.push_back(pnt);
    }
    
    /** 
      * @brief sort the vector for nearest neighbor search
      */ 
    void sort()
    {
        // don't sort if done
        if (sorted) return;
        
        sort(kdVec.begin(), kdVec.end(), X);
        
        sorted = true;
    }
    
    /** 
      * @brief find the nearest point in the cloud
      */ 
    const point<T>& findNearest(const point<T>& pnt) const
    {
        return find(kdVec.begin(), kdVec.end(), X, pnt);
    }
    
    /**
      * @brief binary functions to sort each axis
      */
    static double distSq(const point<T>& left, const point<T>& right) 
    {
        return (left.x()-right.x())*(left.x()-right.x()) 
            + (left.y()-right.y())*(left.y()-right.y()) 
            + (left.z()-right.z())*(left.z()-right.z());
    }

private:
    enum axis {X, Y, Z};

    /**
      * @brief binary functions to sort each axis
      */
    static bool xComp(const point<T>& left, const point<T>& right) {return left.x() < right.x();}
    static bool yComp(const point<T>& left, const point<T>& right) {return left.y() < right.y();}
    static bool zComp(const point<T>& left, const point<T>& right) {return left.z() < right.z();}
    
    /**
      * @brief recursive sort function that cycles through axes
      */
    void sort(typename std::vector<point<T> >::iterator startIt, typename std::vector<point<T> >::iterator endIt, axis a)
    {
        // nothing to sort
        if (startIt == endIt) return;
        
        // sort appropriate axis and index to next axis
        if (a == X) 
        {
            std::sort(startIt, endIt, xComp);
            a = Y;
        }
        else if (a == Y) 
        {
            std::sort(startIt, endIt, yComp);
            a = Z;
        }
        else 
        {
            std::sort(startIt, endIt, zComp);
            a = X;
        }
        
        // find median and recursively sort each side
        unsigned int median = (endIt - startIt)/2;
        sort(startIt, startIt + median, a);
        sort(startIt + median + 1, endIt, a);
    }
    
    /**
      * @brief recursive find function that cycles through axes
      */
    const point<T>& find(typename std::vector<point<T> >::const_iterator startIt, typename std::vector<point<T> >::const_iterator endIt, axis a, const point<T>& findPnt) const
    {
        // find median
        unsigned int median = (endIt - startIt)/2;
        typename std::vector<point<T> >::const_iterator medIt = startIt + median;
        
        // only one point, return
        if (medIt == startIt) return *medIt;
        
        double dist1, dist2, dist3;
        int dir;

        // compare to median and find direction to search
        if (a == X)
        {
            a = Y;
            if (xComp(findPnt, *medIt)) dir = -1;
            else if (xComp(*medIt, findPnt)) dir = 1;
            else dir = 0;
        }
        else if (a == Y)
        {
            a = Z;
            if (yComp(findPnt, *medIt)) dir = -1;
            else if (yComp(*medIt, findPnt)) dir = 1;
            else dir = 0;
        }
        else
        {
            a = X;
            if (zComp(findPnt, *medIt)) dir = -1;
            else if (zComp(*medIt, findPnt)) dir = 1;
            else dir = 0;
        }
        
        if (dir == -1 || (dir == 0 && endIt - medIt < 2))
        {
            // search left (including when equal but nothing to search on the right
            const point<T>& p1 = find(startIt, medIt, a, findPnt);
            dist1 = distSq(p1, findPnt);
            // also compare to this point
            dist2 = distSq(*medIt, findPnt);
            if (dist1 < dist2) return p1;
            else return *medIt;
        }
        else if (dir == 1)
        {
            // search right, if something is there
            if (endIt - medIt < 2) return *medIt;
            
            const point<T>& p1 = find(medIt+1, endIt, a, findPnt);
            dist1 = distSq(p1, findPnt);
            // also compare to this point
            dist2 = distSq(*medIt, findPnt);
            if (dist1 < dist2) return p1;
            else return *medIt;
        }
        else
        {
            // equal so search left and right (artifact of the way we sort)
            const point<T>& p1 = find(startIt, medIt, Y, findPnt);
            dist1 = distSq(p1, findPnt);
            const point<T>& p2 = find(medIt+1, endIt, Y, findPnt);
            dist2 = distSq(p2, findPnt);
            // also compare to this point
            dist3 = distSq(*medIt, findPnt);
            if (dist1 < dist2 && dist1 < dist3) return p1;
            else if (dist2 < dist1 && dist2 < dist3) return p2;
            else return *medIt;
        }
    }

    std::vector<point<T> > kdVec;
    bool sorted;
};

int main(int argc, char** argv)
{
    // generate a random (largish) number of points
    srand((unsigned int)time(0));
    unsigned int numPoints = 100000 + std::rand() % 800000;
    
    // generate points and add to vector
    kdVector<double> kdVec;
    point<double> tempPoint;
    for (unsigned int i = 0; i < numPoints; ++i)
    {
        tempPoint.x() = static_cast<double>(std::rand() % 10000)/100.;
        tempPoint.y() = static_cast<double>(std::rand() % 10000)/100.;
        tempPoint.z() = static_cast<double>(std::rand() % 10000)/100.;
        kdVec.addPoint(tempPoint);
    }
    
    // get another point and find nearest
    tempPoint.x() = static_cast<double>(std::rand() % 10000)/100.;
    tempPoint.y() = static_cast<double>(std::rand() % 10000)/100.;
    tempPoint.z() = static_cast<double>(std::rand() % 10000)/100.;


    kdVec.sort();
    point<double> nearPoint = kdVec.findNearest(tempPoint);
    
    std::cout << "tempPoint: " << tempPoint.x() << ", " << tempPoint.y() << ", " << tempPoint.z() << std::endl;
    std::cout << "nearPoint: " << nearPoint.x() << ", " << nearPoint.y() << ", " << nearPoint.z() << std::endl;
    std::cout << "distance : " << std::sqrt(kdVector<double>::distSq(tempPoint, nearPoint)) << std::endl;

    return 0;
}