#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <type_traits>
#include <cctype>

enum tokenize_options
{
    tokenize_skip_empty_tokens              = 1 << 0,
    tokenize_include_delimiters             = 1 << 1,
    tokenize_exclude_whitespace_delimiters  = 1 << 2,
    //
    tokenize_options_none    = 0,
    tokenize_options_default =   tokenize_skip_empty_tokens 
                               | tokenize_exclude_whitespace_delimiters
                               | tokenize_include_delimiters,
};

template <typename Input, typename Delimiters, typename Out>
   Out tokenize(
           Input const& input,
           Delimiters const& delim,
           Out out,
           tokenize_options options = tokenize_options_default
        )
{
    // decode option flags
    const bool includeDelim   = options & tokenize_include_delimiters;
    const bool excludeWsDelim = options & tokenize_exclude_whitespace_delimiters;
    const bool skipEmpty      = options & tokenize_skip_empty_tokens;

    using namespace std;
    string accum;

    for(auto it = begin(input), last = end(input); it != last; ++it)
    {
        if (find(begin(delim), end(delim), *it) == end(delim))
        {
            accum += *it;
        }
        else
        {
            // output the token
            if (!(skipEmpty && accum.empty()))
                *out++ = accum;   // optionally skip if `accum.empty()`?

            // output the delimiter
            bool isWhitespace = std::isspace(*it) || (*it == '\0'); 
            if (includeDelim && !(excludeWsDelim && isWhitespace))
            {
                *out++ = { *it }; // dump the delimiter as a separate token
            }

            accum.clear();
        }
    }

    if (!accum.empty())
        *out++ = accum;

    return out;
}

int main()
{
    // let's print tokens to stdout
    std::vector<std::string> tokens;

    tokenize("asd sdf qwe wer,sdf;wer", " ;,", 
             std::back_inserter(tokens)/*, tokenize_options_none*/);

    // as a bonus, let's sort them!
    std::sort(tokens.begin(), tokens.end());
    for (std::string token : tokens)
        std::cout << token << "\n";
    // that's all, folks
}

