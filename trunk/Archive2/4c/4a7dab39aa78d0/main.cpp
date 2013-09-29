#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <cctype>

#if (__cplusplus <= 199711L) // patch up missing c++11 support
template <typename T, size_t N> T* begin(T(&p)[N]) { return p;   } 
template <typename T, size_t N> T* end  (T(&p)[N]) { return p+N; } 
#endif

enum tokenize_options
{
    tokenize_skip_empty_tokens              = 1 << 0,
    tokenize_include_delimiters             = 1 << 1,
    tokenize_exclude_whitespace_delimiters  = 1 << 2,
    //
    tokenize_options_none    = 0,
    tokenize_options_default =   tokenize_skip_empty_tokens 
                               | tokenize_exclude_whitespace_delimiters
                               | tokenize_include_delimiters
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
    typedef typename Input::const_iterator In;

    for(In it = input.begin(), last = input.end(); it != last; ++it)
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
                *out++ = std::string(1, *it); // dump the delimiter as a separate token
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
    std::ostream_iterator<std::string> out(std::cout, "\n"); 

    std::string s("asd sdf qwe wer,sdf;wer");
    tokenize(s, " ;,", out);

    // that's all, folks
}
