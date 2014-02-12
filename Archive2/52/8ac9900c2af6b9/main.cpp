#include <boost/filesystem.hpp>

int main() {
    boost::filesystem::create_directories(
       "a/b/c/d/e/../f/../g/../h/../../i/../j/../k/../../../lmnopq/rustvw../../xyz"
    );
}
