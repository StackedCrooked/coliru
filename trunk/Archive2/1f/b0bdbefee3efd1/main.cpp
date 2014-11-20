#include <algorithm>
#include <iterator>
#include <string>
#include <vector>

#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::CharacterVector sort_example(Rcpp::CharacterVector input)
{
	using std::begin; using std::end;
	std::vector<std::string> intermediate(begin(input), end(input));
	std::sort(begin(intermediate), end(intermediate));
	Rcpp::CharacterVector output(begin(intermediate), end(intermediate));
    return output;
}

/*** R

words_before = c("ak", "vj", "jhop", "vv")
words_before
words_after = sort_example(words_before)
words_after

*/
