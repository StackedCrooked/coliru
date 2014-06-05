#include <vector>
#include <string>
#include <sstream>
#include <iostream>

std::vector<std::string> devSplit(const std::string &str) {
    std::istringstream iss(str);
    std::vector<std::string> vect;
    std::string word;
    
    static std::vector<std::string> values =
    {
        "dev_addr = ",
        "dev_type = ",
        "dev_name = ",
        "config_methods = ",
        "dev_capab = ",
        "group_capab = ",
        "dev_info = "
    };
    
    for(int v = 0; std::getline(iss, word, '='); v++) {
        iss >> word;
        vect.push_back(values[v] + word);
    }
    
    return vect;    
}


int main() {
    
    for (std::string v : devSplit("P2P-DEVICE-FOUND fa:7b:7a:42:02:13 "
                      "p2p_dev_addr=fa:7b:7a:42:02:13 "
                      "pri_dev_type=1-0050F204-1 "
                      "name='p2p-TEST1' config_methods=0x188 "
                      "dev_capab=0x27 group_capab=0x0 "
                      "wfd_dev_info=000006015d022a0032"))
        std::cout << v << std::endl;
    
    return 0;
}
