#include <iostream>
#include <cstdint>

/* Do not modify these types. */
using json_int = int64_t;
using json_float = double;
using json_string = struct{ char const * const data_; }; // Simplified for convenience
using json_map = struct{ json_string data_; };
using json_array = struct{ json_string data_; };
using json_null = struct{}; /* json_value's default type */

/*** For the above types, compose a type, json_value, that can hold any of them, but nothing else. */
// Boost and C++11 stdlib allowed; include only what you need.


/*** Given the above type, json_value, ensure that these tests compile and run. */

// Outputs internal data type;
//  string: surround in quotes
//  map/array: display data_
//  null: outputs 'null' (no quotes)
void show(json_value const &jv)
{ std::cout << jv << std::endl; } // Do not modify this function

int main() // Do not modify this function
{
    json_value const jv_s{ "meow" }, jv_i{ 42 }, jv_m{ json_map{ "{}" } };
    show(jv); show(jv_i); show(jv_m);
    
    json_value jv;
    show(jv);
    jv = json_array{ "[]" };
    show(jv);
    jv = 42.0;
    show(jv);
}

/*** Notes:
 * The type can be implemented a couple ways (that we consider good):
 * custom tagged union (variant), custom inheritance-based type erasure (any)
 * 
 * The tagged union is the most difficult, bust most optimal. The any-based approach
 * is easier to compose, but less performant and, by design, dangerously flexible.
 * Flexibility is not needed when we have a fixed set of types. If they use an any approach
 * give brownie points for usage of enable_if and SFINAE to handle non-json types.
 * 
 * Look for code duplication in functions with different types. Could it have been made
 * more generic? The json_string type has been made to not be a std::string, since that
 * would make the union-wrangling more complex (and impossible pre-C++11).
 * 
 * IF YOU SEE ANY void*, THAT'S BAD. NO void* SHOULD BE USED/NEEDED.
 */
 