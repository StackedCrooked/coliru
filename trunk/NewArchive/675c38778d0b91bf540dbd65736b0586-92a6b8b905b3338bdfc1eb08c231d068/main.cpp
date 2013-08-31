#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

typedef std::pair<int, unsigned int> OMKey;     // String, DOM
typedef double OMGeo;
typedef std::vector< std::pair<OMKey, OMGeo> > Geometry;
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
    geo.push_back(std::make_pair(included_key, 0));
    geo.push_back(std::make_pair(extra_key, 0));
    
    for (Geometry::const_iterator i_geo = geo.begin(); i_geo != geo.end(); ++i_geo) {
        const OMKey& key = i_geo->first;
        RecoPulseSeriesMap::const_iterator found_element = pulse_series_map.find(key);
        if (found_element != pulse_series_map.end()) {
            std::cout << "I found (" << key.first << ", " << key.second << ")\n";
        } else {
            std::cout << "I did not find (" << key.first << ", " <<  key.second << ")\n";
        }
    }
    
    return 0;
}

