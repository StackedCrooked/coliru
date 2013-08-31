#include <assert.h>

#include <vector>
#include <algorithm>
#include <iostream>

#include <boost/spirit/include/qi.hpp>

void cleanequal(std::string& s){
    std::replace(s.begin(), s.end(), '=', ' ');
}

std::string get_cell_value(const char* coordinate_b, const char* coordinate_e);
std::string expand_cell_references(std::string const& formula);

//localiza pelo numero maximo de coisas que ele vai ler
static std::vector<std::vector<std::string> > matris;

int main() {
    //inicia-se o loop
    {
        using namespace boost::spirit;

        std::cin.unsetf(std::ios::skipws);
        istream_iterator f(std::cin), l;

        // parse lines of tab-separated values into matris; skipping spaces
        bool ok = qi::phrase_parse(f,l, +~qi::char_("\t\n") % '\t' % '\n', ' ', matris);
        assert(ok);
    }

    // unused, but just to show you how to do it:
    std::vector<int> vetorDeNumeros(matris.size());
    std::transform(matris.begin(), matris.end(), vetorDeNumeros.begin(), mem_fun_ref(&std::vector<std::string>::size));
    // optionally sort it: std::sort(vetorDeNumeros.begin(), vetorDeNumeros.end());
    // or just use std::min_element/std::max_element

    // to remove all equal signs
    for (auto& row : matris)
        for (auto& cell : row)
            cleanequal(cell);

    // to expand all cell references; not that the implementation is virtually unchanged
    for (auto& row : matris)
        for (auto& cell : row)
            cell = expand_cell_references(cell);

    // debug print the resulting matrix
    for (auto& row : matris)
    {
        std::copy(row.begin(), row.end(), std::ostream_iterator<std::string>(std::cout, "\t"));
        std::cout << '\n';
    }
    
    //system("pause");
}

std::string get_cell_value(const char* coordinate_b, const char* coordinate_e)
{
    size_t col = 0, row = 0;
    const char* it;
    for (it=coordinate_b; it != coordinate_e; ++it)
    {
        if (*it >= 'A' && *it <= 'Z')
            col = 26*col + (*it - 'A');
        if (*it >= '0' && *it <= '9')
            row = 10*row + (*it - '0'); /* or use atoi and friends */
    }
    row--; /* 1-based row nums in Excel */

    if (row<matris.size() && col<matris[row].size())
        return matris[row][col];
    else
    return "#INVALID_REFERENCE#";
}

template<typename It, typename Out>
Out expand_cell_references(It f, It const l, Out o)
{
    enum parser_state {
        other,
        in_coord_col,
        in_coord_row
    } state = other;

    /*temporary storage for coordinates being parsed:*/
    char accum[16] = {0};
    char* accit = accum;
    while (f!=l)
    {
        switch(state) /*dummy, the transitions flow in fallthrough order for now*/
        {
            case other:
                *(accit = accum) = 0; /*reset the accumulator*/
                while (f!=l && !(*f>='A' && *f<='Z'))
                    *o++ = *f++;
                /*fallthrough*/
            case in_coord_col:
                while (f!=l && *f>='A' && *f<='Z')
                    *accit++ = *f++;
                /*fallthrough*/
            case in_coord_row:
                {
                    if (f!=l && *f>='0' && *f<='9')
                    {
                        while (f!=l && *f>='0' && *f<='9')
                            *accit++ = *f++;

                        auto expanded = get_cell_value(accum, accit);
                        o = std::copy(expanded.begin(), expanded.end(), o);
                    } else
                    {
                        o = std::copy(accum, accit, o);
                    }
                    continue; /*state = other;*/
                }
        }
    }
    return o;
}

std::string expand_cell_references(std::string const& formula)
{
    std::string expanded;
    expanded.reserve(formula.size());
    expand_cell_references(formula.begin(), formula.end(), std::back_inserter(expanded));
    return expanded;
}
