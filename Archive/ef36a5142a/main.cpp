#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <cassert>

using namespace std;

using StopId = const char*;

StopId make_atom(string const& value)
{
    static set<string> interned;
    auto atom = interned.insert(value);
    return atom.first->c_str();
}

struct LongLat { 
    LongLat(string const& degLong, string const& degLat)
        : lng(deg2rad(mystrtod(degLong))),
          lat(deg2rad(mystrtod(degLat)))
    {
    }
    double lng, lat; 
  private:
    static double deg2rad(double deg) {
        static const double PI = atan(1)*4;
        return deg * PI / 180.0;
    }
    static double mystrtod(string s) {
        return strtod(s.c_str(), nullptr);
    }
};

struct Stop
{
    string fullname;
    LongLat longlat;
};

struct Edge
{
    StopId dest, source;
    double cost;
};

using Stops = unordered_map<StopId, Stop>;
using Edges = vector<Edge>;

namespace std {
    template <> struct hash<Edge> {
        size_t operator()(Edge const& e) const 
        { 
            static const hash<const char*> h_ = {};
            return h_(e.dest) ^ (37*h_(e.source)); 
        }
    };
}

vector<string> split(string const& line, const char sep=',')
{
    vector<string> cols;
    istringstream iss(line);

    string v;
    if (',' == sep) // ugly hack
    {
        getline(iss, v, sep);
        cols.push_back(move(v));

        char quote;
        iss >> quote;
        assert('"' == quote);
        getline(iss, v, '"');
        cols.push_back(move(v));
        iss.ignore(1024, sep);
    }

    while (iss)
    {
        getline(iss, v, sep);
        if (!iss)
            break;
        cols.push_back(move(v));
    }

    if (iss || iss.eof())
        return cols;
    throw runtime_error("Failed to parse record");
}

Stops readStops()
{
    cin.clear();
    size_t number;
    cin >> number;
    cin.ignore(1024, '\n');

    Stops stops;
    while (cin && number--)
    {
        string line;
        getline(cin, line);
        auto cols = split(line);

        assert(cols.size() >= 7);

        string id          = cols[0];
        string fullname    = cols[1];
        LongLat longlat    = { cols[4], cols[3] };

        stops.insert({make_atom(id), { fullname, longlat }});

        if (!cin)
            throw runtime_error("Failed to parse stop record, " + to_string(number) + "remaining");
    }

    if (cin || cin.eof())
        return stops;
    throw runtime_error("Failed to parse file");
}

Edges readEdges()
{
    cin.clear();
    size_t number;
    cin >> number;
    cin.ignore(1024, '\n');

    Edges edges;
    while (cin && number--)
    {
        string line;
        getline(cin, line);
        auto cols = split(line, ' ');

        assert(cols.size() == 2);

        edges.push_back({ make_atom(cols[1]), make_atom(cols[0]) });

        if (!cin)
            throw runtime_error("Failed to parse edge record, " + to_string(number) + "remaining");
    }

    if (cin || cin.eof())
        return edges;
    throw runtime_error("Failed to parse file");
}

double distance(LongLat const& a, LongLat const& b)
{
    auto x = (b.lng - a.lng) * cos((a.lat + b.lat)/2.0);
    auto y = (b.lat - a.lat);
    return sqrt(x*x + y*y) * 6371;
}

int main()
{
    //setlocale(LC_NUMERIC, "fr_FR"); // Doesn't work in codinggames... 
    setlocale(LC_NUMERIC, "C");

    ////////////////////////////////////////////////////////////////////
    ////// read source and destination
    string journey_begin, journey_destination;
    getline(cin, journey_begin);
    getline(cin, journey_destination);
    auto const startId       = make_atom(journey_begin);
    auto const destinationId = make_atom(journey_destination);

    ////////////////////////////////////////////////////////////////////
    ////// read stops and edges
    auto const stops = readStops();
    auto edges = readEdges();

    ////////////////////////////////////////////////////////////////////
    ////// precalculate edge costs and order by proximity
    for(auto& e : edges)
        e.cost = distance(stops.at(e.source).longlat, stops.at(e.dest).longlat);

    // Optimize edge ordering; 
    // 1. We store subranges ranked by destination node (for easy lookup of
    //    incoming edges by destination stop)
    // 2. Within each subrange, order incoming edges by descending proximity to
    //    the startId (journey_begin) - the heuristic is that routes will
    //    usually end up shortest when going to a station closer to the search
    //    target sooner.
    {
        auto startLonglat = stops.at(startId).longlat;
        auto proximity    = [&](StopId id) { return distance(stops.at(id).longlat, startLonglat); };
    
        sort(begin(edges), end(edges), [&](Edge const& a, Edge const& b) {
            return make_tuple(a.dest, proximity(a.source)) < make_tuple(b.dest, proximity(b.source));
        });
    }

    ////////////////////////////////////////////////////////////////////
    ////// The algorithm, a DFS with branch pruning and cycle prevention
    auto find_shortest_route = [&](StopId node, vector<Edge const*>& best_route) 
    {
        // state
        best_route.clear();
        vector<Edge const*> current_route;
        double current_cost = 0, best_cost = numeric_limits<double>::max();

        // branch pruning
        unordered_map<StopId, double> best_known;

        // locals
        auto by_dest   = [](Edge const& a, Edge const& b){ return a.dest    < b.dest; };

        function<bool(Edge const&)> recurse = [&](Edge const& edge) {
            auto node = edge.source;

            if (end(current_route) != find_if(begin(current_route), end(current_route),
                        [&](Edge const* e){ return e->source == node; }))
                return true; // no cycles

            auto prev_cost = current_cost;
            current_cost += edge.cost;

            if (current_cost >= best_cost)
            {
                current_cost = prev_cost;
                return true;
            }

            current_route.push_back(&edge);
            bool possible = true;

            if (node == startId)
            {
                if (current_cost < best_cost)
                {
                    accumulate(begin(current_route), end(current_route), 0.0,
                            [&](double cumul, Edge const* e) // mutable
                            {
                                cumul += e->cost;
                                auto tryinsert = best_known.insert({e->source, cumul});
                                if (!tryinsert.second)
                                    tryinsert.first->second = min(tryinsert.first->second, cumul);
                                return cumul;
                            });

                    best_route = current_route;
                    best_cost  = current_cost;
                }
            } 
            else if (current_cost < best_cost)
            {
                auto cached = best_known.find(node);
                if (end(best_known) == cached || (current_cost < cached->second))
                {
                    auto incoming = equal_range(begin(edges), end(edges), Edge {node}, by_dest);

                    possible = accumulate(incoming.first, incoming.second, false,
                            [&] (bool accum, Edge const& e) { return recurse(e) || accum; });
                }
            }

            current_cost = prev_cost;
            current_route.pop_back();

            return possible;
        };

        if (startId == node)
            return true;

        // bootstrap the search
        auto roots = equal_range(begin(edges), end(edges), Edge {node}, by_dest);

        return accumulate(roots.first, roots.second, false,
                    [&] (bool accum, Edge const& e) { return recurse(e) || accum; });
    };

    vector<Edge const*> result;

    if (find_shortest_route(destinationId, result))
    {
        reverse(begin(result), end(result));
        for(auto const& stop : result)
            cout << stops.at(stop->source).fullname << "\n";
        cout << stops.at(destinationId).fullname << "\n";
    } else
    {
        cout << "IMPOSSIBLE\n";
    }
}
