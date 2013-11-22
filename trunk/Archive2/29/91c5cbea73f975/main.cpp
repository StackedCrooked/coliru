#include <vector>
#include <map>
#include <string>
int main()
{
    #define makevec(x) std::vector<std::vector<int>>(x, std::vector<int>(x))
    std::map<std::string, std::vector<std::vector<int>>> pData{{"OverallArrivalAlgorithm_Blocks", makevec(1)},
                                                                {"BusyArrivalAlgorithm_Blocks", makevec(1)},
                                                                {"firstBusyHourArrivalIndex", makevec(1)},
                                                                {"lastBusyHourArrivalIndex", makevec(1)},
                                                                {"numOverallArrivals", makevec(1)},
                                                                {"numBusyArrivals", makevec(1)}};
}