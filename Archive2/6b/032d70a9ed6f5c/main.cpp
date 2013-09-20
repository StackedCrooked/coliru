#include <memory>
#include <vector>
#include <algorithm>
//#include <iterator>

typedef std::unique_ptr<int> unique_t;
typedef std::vector< unique_t > vector_t;

int main()
{
    vector_t vec1;                       // fine
    vector_t vec3(std::make_move_iterator(vec1.begin()), std::make_move_iterator(vec1.end())); // fine!

    std::sort(vec1.begin(), vec1.end()); // fine, because using Move assignment

    vector_t vec4;
    std::move(vec1.begin(), vec1.end(), std::back_inserter(vec4)); // fine!
}
