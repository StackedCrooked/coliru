#include <boost/container/flat_map.hpp>
#include <boost/icl/interval_set.hpp>
#include <boost/icl/separate_interval_set.hpp>
#include <boost/icl/split_interval_set.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/range/algorithm.hpp>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <map>
#include <random>

namespace icl = boost::icl;

using Position = size_t;
using Map      = icl::interval_set<Position>;
using Region   = Map::value_type;
using Relocs   = boost::container::flat_multimap<Position, Region>;

struct Generator {
    Generator(std::string const& input) 
        : _input(input),
          _dashes(region_map(_input.begin(), _input.end())),
          _rng(std::random_device {}()),
          _select (0, _dashes.iterative_size() - 1),
          _randpos(0, _input.size() - 1),
          _is_degenerate(cardinality(_dashes) == _input.size())
    {
    }

    unsigned random(unsigned below) {
        return _rng() % below; // q&d, only here to make the tests deterministic for a fixed seed
    }

    Map full() const { 
        return Map { { 0, _input.size() } };
    }

    Relocs gen_relocations(int n=1) {
        Map const moving = pick_dashes(n);

        Relocs relocs;
        relocs.reserve(moving.iterative_size());

        if (_is_degenerate)
        {
            // degenerate case (everything is a dash); no non-moving positions
            // exist, just pick 0
            for(auto& region : moving)
                relocs.emplace(0, region);
        } else {
            auto inertia = [&] {
                Position inert_point;
                while (contains(moving, inert_point = _randpos(_rng)))
                    ; // discard insertion points that are moving
                return inert_point;
            };

            for(auto& region : moving)
                relocs.emplace(inertia(), region);
        }

        return relocs;
    }

    template <typename Out>
        Out apply_relocations(Relocs const& mobility, Out out) const {
            if (_is_degenerate)
                return std::copy(_input.begin(), _input.end(), out);
            
            auto to_iter = [this](Position pos) { return _input.begin() + pos; };

            do_apply_relocations(mobility, [&](Region const& r, bool relocated) {
                if (relocated) *out++ = '(';
                out = std::copy(
                    to_iter(first(r)),
                    to_iter(last(r)+1),
                    out
                );
                if (relocated) *out++ = ')';
            });

            return out;
        }

    template <typename F>
        void do_apply_relocations(Relocs const& mobility, F const& apply) const {
            icl::split_interval_set<Position> steps {{0, _input.size()}};

            for (auto& m : mobility) {
                steps += m.first; // force a split on insertion point
                steps -= m.second; // remove the source of the move
                //std::cout << m.second << " moving to #" << m.first << ": " << steps << "\n";
            }

            auto next_mover = mobility.begin();

            for(auto& step : steps) {
                while (next_mover!=mobility.end() && contains(step, next_mover->first))
                    apply((next_mover++)->second, true);

                apply(step, false);
            }
        }

    Map pick_dashes(int n) {
        Map map;
        if (!_dashes.empty())
            for (int i = 0; i < n; ++i)
                map += *std::next(_dashes.begin(), _select(_rng));
        return map;
    }

  private:
    std::string                             _input;
    Map                                     _dashes;
    std::mt19937                            _rng;
    std::uniform_int_distribution<Position> _select;
    std::uniform_int_distribution<Position> _randpos;
    bool                                    _is_degenerate;

    template <typename It> Map region_map(It f, It l) {
        Map dashes;

        for (Position pos = 0; f!=l; ++f, ++pos)
            if ('-' == *f)
                dashes += pos;

        return dashes;
    }
};

#include <boost/range/reverse_iterator.hpp>

std::string mark_sequence(std::string input, Map const& moves) {
    for (auto it = moves.rbegin(); it != moves.rend(); ++it) {
        auto& r = *it;
        input.insert(last(r)+1, 1u, ')');
        input.insert(first(r),  1u, '(');
    }
    return input;
}

int main() {
    std::random_device rnddev{};
    std::default_random_engine rndengine{ rnddev() };

    for (std::string example : {
            "----",
            "A--TG-DF----GR--",
            "",
            "ATGDFGR",
            "--A--B-CD----E-F---",
        })
    {
        auto start = std::chrono::high_resolution_clock::now();

        Generator gen(example);

        std::string result;
        std::map<std::string, size_t> histo;

        for (int i = 0; i < 1000000; ++i) {
            auto const moves = gen.pick_dashes(1);
            histo[mark_sequence(example, moves)]++;
        }

        std::cout << histo.size() << " unique results for '" << example << "'"
                  << " in " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()-start).count() << "ms\n";

        std::multimap<size_t, std::string, std::greater<size_t> > ranked;
        for (auto& entry : histo)
            ranked.emplace(entry.second, entry.first);

        int count = 10;
        for (auto& rank : ranked)
        {
            std::cout << std::setw(8) << std::right << rank.first << ": " << rank.second << "\n";
            if (0 == --count)
                break;
        }
    }
}
