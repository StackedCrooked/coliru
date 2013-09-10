#include <cstring> // for memcpy
#include <iostream>
#include <unordered_map>
#include <vector>
#include <boost/uuid/sha1.hpp>

static void find_duplicate_rows(int** array, size_t n, size_t m)
{
    // initialize a hash map - from unsigned int to indices
    typedef std::vector<size_t> indices_vector;
	typedef std::unordered_map<unsigned int, indices_vector> hash_to_indices;

	hash_to_indices hash_map;
	unsigned int digest[5];

	for ( size_t i=0; i<n; i++ ) {
        // compute hash of line i
		boost::uuids::detail::sha1 sha1;
		sha1.process_bytes(array[i], m*sizeof(int));
		sha1.get_digest(digest);
        // we use only the first integer, but this should be fine
		const unsigned int key = digest[0];

		indices_vector& indices = hash_map[key];
        
        // if the key is new, just save it. otherwise, print it.
		if (indices.empty()) {
            indices.push_back(i);
		}
        else {
            std::cout << i << std::endl;
    		// before printing we need to handle collisions - compare all lines
            // with equal hash to see if they contains the same elements.
        }
	}
}

static const size_t N = 5;
static const size_t M = 6;
static int data[N][M] = {
	{1,2,3,4,5,6},
	{5,4,3,2,1,6},
	{1,1,1,1,1,1},
	{1,2,3,4,5,6},
	{1,1,1,1,1,1},
};

// should print 3 and 4
int main()
{
    // copy array to int**
    int** array = new int*[N];
	for (size_t i=0; i<N; i++) {
		array[i] = new int[M];
		::memcpy(array[i], data[i], sizeof(int)*M);
	}
    
    // actual function call
    find_duplicate_rows(array, N, M);
    
    // delete int**
    for (size_t i=0; i<N; i++) {
		delete array[i];
	}
	delete array;
}
