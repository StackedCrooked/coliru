    #include <stdio.h>
    #include <time.h>
    #include <mutex>
    #include <iostream>
    #include <vector>
    #include <bitset>
    #include <sstream>
    #include <iomanip>
    

class SystemSettingIdentifier;
static std::vector<SystemSettingIdentifier> mapOfSettings;

class SystemSettingIdentifier{
    int systemSettingId;
    std::string systemSettingName;
    public:
    SystemSettingIdentifier(int systemSettingId, std::string systemSettingName) : systemSettingId(systemSettingId), systemSettingName(systemSettingName){
        mapOfSettings.push_back(*this);
    }
    operator int(){
        return systemSettingId;
    }
};

#define ENUMFIELD(FIELDOFENUM,VALUEOFENUM) class FIELDOFENUM  : public SystemSettingIdentifier {   public:      FIELDOFENUM(): SystemSettingIdentifier(VALUEOFENUM,std::string("FIELDOFENUM")){}; } FIELDOFENUM

class SystemSettings {
    public:
     ENUMFIELD(CdrDateTimeField,111);
     ENUMFIELD(MaxSQLBufferTimeout,165);
     ENUMFIELD(CdrRateBufferLimit,409);
     ENUMFIELD(BytesToReserveOnPrepaidCredit,476);
     
} SystemSettings;


void getValueOfSS(SystemSettingIdentifier s){
    std::cout << "value of SystemSetting is" << (int)s;
}


int main(){
     
    getValueOfSS(SystemSettings.CdrDateTimeField);

}