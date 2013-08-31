#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

typedef std::pair<int, unsigned int> OMKey;     // String, DOM
typedef std::vector<OMKey> Geometry;
typedef std::pair<double, double> RecoPulse;    // Time, Charge
typedef std::vector<RecoPulse> RecoPulseSeries;
typedef std::map<OMKey, RecoPulseSeries> RecoPulseSeriesMap;

int main()
{
    OMKey included_key = std::make_pair(83, 40);
    OMKey extra_key = std::make_pair(83, 41);
    
    RecoPulseSeries pulse_series;
    pulse_series.push_back(std::make_pair(9793.72, 0.879));
    pulse_series.push_back(std::make_pair(10102.29, 1.127));
    
    RecoPulseSeriesMap pulse_series_map;
    pulse_series_map[included_key] = pulse_series;
    
    Geometry geo;
    geo.push_back(included_key);
    geo.push_back(extra_key);
    
    for (Geometry::const_iterator i_geo = geo.begin(); i_geo != geo.end(); ++i_geo) {
        RecoPulseSeriesMap::const_iterator found_element = pulse_series_map.find(*i_geo);
        if (found_element != pulse_series_map.end()) {
            const OMKey& found_key = found_element->first;
            std::cout << "I found (" << found_key.first << ", " << found_key.second << ")\n";
        } else {
            const OMKey& not_found_key = *i_geo;
            std::cout << "I did not find (" << not_found_key.first << ", " <<  not_found_key.second << ")\n";
        }
    }
    
    return 0;
}

