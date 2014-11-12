#include "misc/Vector.h"
#include "misc/IntTuple.h"
#include <list>

#include <ext/hash_map>

class GridSubdivision
{
public:
  typedef IntTuple Index;
  typedef std::list<void*> ObjectSet;
  //called once per object in the query range, return false to stop enumerating
  typedef bool (*QueryCallback)(void* obj);

  GridSubdivision(int numDims,double h=1);
  GridSubdivision(const Vector& h);
  size_t GetBucketCount() const { /*return buckets.bucket_count();*/ return buckets.size();} // Nuttapong }
  void SetBucketCount(size_t n) {
#ifdef WIN32
    //buckets.rehash(n);
     //buckets.resize(n);
#else
    buckets.resize(n);
#endif
  }
  void SetHashPower(size_t n) {
#ifdef WIN32
#else
    buckets.hash_funct().pow=n;
#endif
  }