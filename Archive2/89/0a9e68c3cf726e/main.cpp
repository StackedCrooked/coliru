#include <vector>
#include <map>
#include <string>
int main()
{
    using twoDvec = std::vector<std::vector<int>>;
    using oneDvec = std::vector<int>;
    std::map<std::string, std::vector<std::vector<int>>> pData{{"OverallArrivalAlgorithm_Blocks", twoDvec(1, oneDvec(1))},
                                                                {"BusyArrivalAlgorithm_Blocks", twoDvec(1, oneDvec(1))},
                                                                {"firstBusyHourArrivalIndex", twoDvec(1, oneDvec(1))},
                                                                {"lastBusyHourArrivalIndex", twoDvec(1, oneDvec(1))},
                                                                {"numOverallArrivals", twoDvec(1, oneDvec(1))},
                                                                {"numBusyArrivals", twoDvec(1, oneDvec(1))}};
}