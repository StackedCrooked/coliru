#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <iterator>

using namespace std;

using Sequence  = string;
using Sequences = vector<Sequence>;

Sequences readProblem() {
    int n;
    if(cin >> n) {
        vector<string> v(n);
        copy_n(istream_iterator<string>(cin), n, begin(v));
        return v;
    }
    exit(255);
}

struct Overlap
{
    size_t idx1, idx2;
    int amount;
};

/// preconditon: sequences order by ascending length
vector<Overlap> findOverlaps(Sequences const& sq)
{
    vector<Overlap> results;

    auto const N = sq.size();
    for (auto i1=0u; i1<N; ++i1)
        for (auto i2=0u; i2<N; ++i2)
            if (i1!=i2)
            {
                auto s1 = sq[i1];
                auto s2 = sq[i2];

                auto c   = s2.front();
                auto pos = s1.find(c);
                for (;string::npos != pos; pos = s1.find(c, pos+1))
                {
                    int amount = s1.size()-pos;
                    if (s2.substr(0, amount) == s1.substr(pos))
                        results.push_back({i1, i2, amount});
                }
            }

    return results;
}

void removeSubsequences(Sequences& sq)
{
    sort(begin(sq), end(sq), [](Sequence const& a, Sequence const& b) { return a.size()<b.size(); });
    auto last = end(sq);
    for (auto i1=begin(sq); i1<last; ++i1)
skip_increment:
        for (auto i2=i1+1; i2<last; ++i2)
        {
            if (string::npos != i2->find(*i1))
            {
                sq.erase(i1);
                --last;

                if (i1==last)
                    return;
                goto skip_increment;
            }
        }
}

int main() {
    set<size_t> solution_sizes;

    function<void(Sequences)> solveSmallest = [&](Sequences problem) mutable
    {
        removeSubsequences(problem);

        // make a scheme of overlaps
        auto overlaps = findOverlaps(problem);
        // sort by overlap amount descending
        sort(begin(overlaps), end(overlaps), [](Overlap const& a, Overlap const& b) { return a.amount>b.amount; });

        if (overlaps.empty())
        {
            solution_sizes.insert(accumulate(begin(problem), end(problem), 0ul, [](size_t accum, string const& s) { return accum + s.size(); }));
        }

        for (auto const& o : overlaps)
        {
            // strength reduction
            Sequences reduced(problem);

            reduced[o.idx1] += reduced[o.idx2].substr(o.amount);
            reduced.erase(reduced.begin()+o.idx2);

            solveSmallest(reduced);
        }
    };

    solveSmallest(readProblem());

    cout << *solution_sizes.begin() << "\n";
}
