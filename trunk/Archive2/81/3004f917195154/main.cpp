    // C++ Solar eclipse program(Shoushi integrated) input as start_year and end_year
    // author : Mr Lam/ Yee Din email : yeedlam@yahoo.com
    // Copyright reserved if you want to use the program, please contact the author
    // Date: August 14, 2014 from http://ideone.com/W2Cevg of January 15, 2013
     
    #include <iostream>
    using namespace std;
    #include <cmath> // or math.h
     
    const int start_year = 1568; // enter start_year
    const int end_year = 1644; // enter end_year
     
    const double YearDays_Sh = 365.2425;
    const double YearDays_HB = 365.24233442;
    const int BaseYear = 1281;
    const double pi = 3.14159265;
    //===========================================================
    // 4 Paramters for adjustments
    const double Qiying_Sh = 55.06 - 0.09, Runying_Sh = 20.2050 - 0.092309;
    const double Jiaoying_Sh = 26.0388 - 0.094472 - 0.09; // - 0.094472 for Xin YunLo data 13.845663;
    const double Zhuanying_Sh = 13.0205 + 0.1425;
    //===========================================================
    // Constants for Moon to determine solar eclipse purpose
    // const double Shuoshi_Sh = 29.530593;
    const double Zhuanzhong = 27.5546;
    const double Jiaozhong = 27.212224;
    const double MonthJiao = 2.318369;
    const double half_Zhuanzhong = Zhuanzhong/2;
    const double Shuoying_Sh = 8.3879 + 1;
    //===================================================
    // Constant for Moon positions : Lead or Lag
    const double MonthMoon = 1.975993;
    const double MoonMeanSpeed = 13.36875;
    //===================================================
    const double Qiying_HB = 32.12254;
    const double Shuoying_HB = 15.12633;
    const double Shuoshi_HB = 29.53059053;
    const double eclipse_seconds_per_day = 110413.92441334;
    const double eclipse_ying = 203 + 36.0/60 + 52.0/3600 + 49.0/(3600 * 60);
    const double month_eclipse = 30 + 40.0/60 + 13.0/3600 + 55.0/(3600 * 60);
    const int seconds_in_cycle = 1296000;
    const double YearsSun_Sh = (1723 - BaseYear)* 62.9975/3600;
     
     
    typedef struct{
    int year; int month; int day;
    double eclipseFrac; double eclipseBegin; double eclipseMax; double eclipseEnd;
    double eclipseBeginS; double eclipseEndS;
    int SunStatus; int MoonStatus;
    int SunStatusS; int MoonStatusS;
    double observed_time; double HalfDayFan;
    double ReqSun; double ReqMoon;
    double Gon;
     
    double EclipseFracS;
    double MoonSp;
     
    double MDayT_hour;
    double observed_timeS;
    double SunXS; double MoonXS; double SunMoonXS;
    } EclipseTime;
     
    EclipseTime eclipse_shoushi[100];
     
    EclipseTime eclipse_theo[]
    = {
    {1568, 9, 21, 0.109955, 11.1367, 11.7366, 12.3428}, // from eclipse.org.uk
    {1572, 6, 10, 0.916, 6.66, 7.93, 9.93},
    {1575, 5, 10, 0.701, 13.05, 14.29, 15.45},
    {1582, 6, 20, 0.723024, 12.2055, 13.6179, 14.9154}, // from eclipse.org.uk
    {1583, 12, 14, 0.825, 11.23, 13.08, 14.77},
    {1587, 10, 2, 0.735831, 11.3223, 12.6436, 13.9343}, // from eclipse.org.uk
    {1589, 2, 15, 0.301344, 6.4499, 7.1961, 7.99914}, // from eclipse.org.uk
    {1590, 7, 31, 0.430839, 16.0803, 17.1059, 18.0372}, // from eclipse.org.uk
    {1594, 5, 20, 0.319, 9.83, 10.84, 11.9},
    {1596, 9, 22, 0.949, 9.87, 11.17, 12.5},
     
    {1603, 5, 11, 0.903, 7.4, 8.59, 9.93},
    {1604, 4, 29, 0.078077, 15.8827, 16.4079, 16.907}, // from eclipse.org.uk
    {1607, 2, 26, 999, 17.32, 18.26, 999}, // no data from eclipse.org.uk
    {1609, 12, 26, 0.044430, 16.197, 16.594, 16.9753}, // from eclipse.org.uk but no apparent noon
    {1610, 12, 15, 0.607, 14.61, 16.07, 17.32},
    {1612, 12, 99, 999, 999, 999, 999}, // no data from eclipse.org.uk
    {1615, 3, 29, 0.889903, 15.1624, 16.4118, 17.5463}, // from eclipse.org.uk
    {1617, 8, 1, 0.470019, 19.07, 19.9041, 20.6909}, // eclipse_fraction, eclipse_maximum, eclipse_end from eclipse.org.uk
    {1621, 5, 21, 0.711, 17.26, 18.26, 19.18},
    {1629, 6, 21, 0.166, 10.98, 11.71, 12.45},
     
    {1631, 10, 25, 0.108, 12.34, 12.91, 13.48},
    {1634, 3, 29, 0.81964, 8.77022, 9.94358, 11.1899 }, // from eclipse.org.uk
    {1636, 8, 1, 0.632763, 8.37958, 9.62653, 10.9643}, // from eclipse.org.uk
    {1637, 1, 26, 0.199, 12.71, 13.68, 14.58},
    {1638, 1, 15, 0.656, 11.65, 13.32, 14.84},
    {1641, 11, 3, 0.827, 12.65, 14.04, 15.33},
    {1643, 3, 20, 0.53, 7.83, 8.85, 9.94},
    {1644, 9, 1, 0.303, 10.93, 12.14, 13.34},
     
    {99999, 0, 0, 0, 0, 0, 0}
    };
     
    enum Status{LagStart, LagEnd, LeadStart, LeadEnd};
    struct Status_type{char *sun; char *moon;};
     
    class Ref_data
    {
    private:
    Status SunStatus, MoonStatus;
     
    protected:
    int calculated_year; int MonthNum;
     
    double total_days; double LeapDay;
    double RefEcl; double RefSun; double RefMoonDay; double RefMoon;
    double ReqEcl; double ReqSun; double ReqMoonDay; double ReqMoon;
    double UseSun;
    double SolarEclipse_angle; int Front;
     
    public:
    Ref_data(int m,int n)
    {
    calculated_year = m; MonthNum = n;
     
    RefEcl = 0; RefSun = 0; RefMoonDay = 0; RefMoon = 0;
    ReqEcl = 0; ReqSun = 0; ReqMoonDay = 0; ReqMoon = 0;
     
    total_days = 0; LeapDay = 0; UseSun = 0;
    }
    ~Ref_data(){}
     
    void checkSunStatus(double HalfYear, double ReqSun, double& UseSun, int& SunStatus)
    {
    SunStatus = LagStart; UseSun = 0;
     
    if (ReqSun < HalfYear)
    {
    SunStatus = LagStart; UseSun = ReqSun;
    if (ReqSun > 93.712025){UseSun = HalfYear - UseSun; SunStatus = LagEnd;}
    }
     
    if (ReqSun > HalfYear )
    {
    SunStatus = LeadStart; UseSun = ReqSun - HalfYear ;
    if (UseSun > 88.909225){UseSun = HalfYear - UseSun; SunStatus = LeadEnd;}
    }
    }
     
    void get_SunX(int SunStatus, double UseSun, int IUseSun,double& SunAdd, double& SunSum, double& SunX)
    {
    SunAdd = SunSum = SunX = 0;
     
    if (fmod(SunStatus, 3.0) == 0) // SunStaus = LagStart & LeadEnd
    {
    SunAdd = 484.8473 -(4.4362 + 0.0162 *(IUseSun - 1)/2)* IUseSun;
    SunSum = (487.06 -(2.21 + 0.0027 * IUseSun)* UseSun)* IUseSun;
    }
     
    if (fmod(SunStatus, 3.0) > 0) // SunStatus = LagEnd & LeadStart
    {
    SunAdd = 510.8569 -(4.9386 + 0.0186 *(IUseSun - 1)/2)*IUseSun;
    SunSum = (513.32 -(2.46 + 0.0031 * IUseSun)*IUseSun)*IUseSun;
    }
    SunX =((UseSun - IUseSun)*SunAdd + SunSum)/10000;
    }
     
    // Calculate Solar eclipse angle
     
    void get_SolarEclipse_angle(int SunStatus,double ReqEcl_angle,double SunX,double& SolarEclipse_angle,int& Front)
    {
    if (SunStatus < LeadStart){SolarEclipse_angle = ReqEcl_angle - abs(SunX);}
    if (SunStatus > LagEnd){SolarEclipse_angle = ReqEcl_angle + abs(SunX);}
     
    if (SolarEclipse_angle < 7){Front = 1;}
    if (SolarEclipse_angle > 342){Front = 1;}
     
    if(SolarEclipse_angle > 202)
    {
    if (SolarEclipse_angle < 342){
    // cout << "==============================" << endl;
    // cout << " no solar eclipse observed" << endl;
    // cout << "==============================" << endl;
    }
    }
     
    if(SolarEclipse_angle < 175)
    {
    if (SolarEclipse_angle > 7){
    // cout << "=================================" << endl;
    // cout << " no solar eclipse observed" << endl;
    // cout << "=================================" << endl;
    }
    }
     
    if (SolarEclipse_angle > 175)
    {
    if ( SolarEclipse_angle < 202){Front = -1;}
    }
    // cout << "=================" << endl;
    // cout << "Front = " << Front << endl;
    // cout << "=================" << endl;
    }
     
    void get_UseMoon(double ReqMoon, double& UseMoon, double& SoD,
    double& moon_x12_2, double& MoonSolar,
    int& MoonStatus, double& MoonLL, double& MoonAdd)
    {
    double moon_84_check;
    if (ReqMoon > half_Zhuanzhong){UseMoon = ReqMoon - half_Zhuanzhong;MoonStatus = LagStart;}
    if (ReqMoon < half_Zhuanzhong){UseMoon = ReqMoon;MoonStatus = LeadStart;}
     
    moon_x12_2 = UseMoon * 12.2;
    SoD = int(moon_x12_2) * 0.082008;
     
    moon_84_check = moon_x12_2;
    if (moon_x12_2 > 84)
    {
    if (MoonStatus == LeadStart){MoonStatus = LeadEnd;}
    if (MoonStatus == LagStart){MoonStatus = LagEnd;}
     
    moon_84_check = 167 - moon_84_check;
    }
    MoonLL = moon_84_check;
     
    MoonSolar = UseMoon - SoD;
     
    if(MoonSolar < 0)
    {
    SoD = SoD - 0.082008;
    MoonSolar = UseMoon - SoD;
     
    if (fmod(MoonStatus, 2.0) == 0){MoonLL = int(MoonLL);}
    if (fmod(MoonStatus, 2.0) > 0){MoonLL = 167 - int(moon_x12_2);}
    }
    MoonAdd = 11.081575 -(0.05815 + 0.00195 *(MoonLL-1)/2)* MoonLL;
    }
     
     
    void get_MoonX(int MoonStatus,double MoonLL,double MoonAdd,double MoonSolar,double& MoonSum, double& MoonX, double& MoonSp)
    {
    MoonSum = 0, MoonX = 0, MoonSp = 0;
     
    switch(MoonStatus)
    {
    case LagStart:
    MoonSp = 0.9855 +(0.05815 + 0.00195 *(MoonLL-1)/2)* MoonLL/100;
    MoonSum =(0.1111 -(0.000281 + 0.00000325 *MoonLL)*MoonLL)*MoonLL;
    MoonX = MoonSum + MoonSolar * MoonAdd/820; break;
     
    case LagEnd:
    MoonSp = 1.2071 -(0.05815 + 0.00195 *(MoonLL-1)/2)*MoonLL/100;
    MoonLL = MoonLL + 1;
    MoonSum =(0.1111 -(0.000281 + 0.00000325 * MoonLL)*MoonLL)*MoonLL;
    MoonX = MoonSum - MoonSolar * MoonAdd/820; break;
     
    case LeadStart:
    MoonSp = 1.2071 -(0.05815 + 0.00195 *(MoonLL-1)/2)*MoonLL/100;
    MoonSum =(0.1111 -(0.000281 + 0.00000325 *MoonLL)*MoonLL)*MoonLL;
    MoonX = MoonSum + MoonSolar * MoonAdd/820; break;
     
    case LeadEnd:
    MoonSp = 0.9855 +(0.05815 + 0.00195*(MoonLL-1)/2)*MoonLL/100;
    MoonLL = MoonLL + 1;
    MoonSum =(0.1111 -(0.000281 + 0.00000325 * MoonLL)*MoonLL)*MoonLL;
    MoonX = MoonSum - MoonSolar * MoonAdd/820; break;
     
    default:
    cout << " no MoonStatus"; break;
    }
    }
     
    };
     
    class base2 {
    protected:
    int k;
    public:
    base2(int x) {k=x;}
    ~base2() {}
    };
     
    class derived: public Ref_data, public base2 {int j;
    public:
    derived(int m, int n, int x, int z): Ref_data(m,n), base2(x){j=z;}
    ~derived() {}
     
    void show() {cout << calculated_year << " " << k << " " << j << "\n";}
    };
     
    int main()
    {
    cout << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt" << "\tt"
    << "\tt" << "\tt" << "\tt" << endl;
     
    cout << "\tSolar eclipse time is in 24 hours\n"
    << "\tBeijing local noon time is 12 as reference\n"
    << "\tmonth means total months from winter solitice\n"
    << "\tReqMDay=ReqMoonDay\n"
    << "year(month)\n";
     
    int index = 0;int Pindex = 0;int calculated_year, MonthNum;
     
    for (calculated_year = start_year; calculated_year - 1< end_year; calculated_year ++)
    {
    for (MonthNum = 0; MonthNum < 14; MonthNum ++)
    {
    //---------------
    // Step 1:
    Ref_data year(calculated_year,MonthNum);
    double YearDays = YearDays_Sh -(int)((calculated_year - BaseYear)/100)*0.0002;
    double HalfYear = YearDays/2;
    double total_days =(calculated_year - BaseYear)* YearDays;
    double Win_Sh = fmod((total_days + Qiying_Sh +(int)(abs(total_days))*60),60);
     
    //**************************************************
    // Integrate HouBian steps to calculate LeapDay
    //**************************************************
    double Itotal_days = total_days +(Qiying_Sh -(int)Qiying_Sh)-(Win_Sh -(int)Win_Sh);
     
    double NetMoonDay_Sh = Itotal_days - Shuoying_Sh;
    double OffMoonDay_Sh = fmod(NetMoonDay_Sh, Shuoshi_HB); // for drift comparison
    if (OffMoonDay_Sh < 0){OffMoonDay_Sh = Shuoshi_HB + OffMoonDay_Sh;}
     
    double RefDays =(int)Win_Sh + 1;
    double RefMoonDay = 60 + RefDays - OffMoonDay_Sh;
    double LeapDay = Win_Sh - RefMoonDay;
    if (LeapDay < 0){LeapDay = 60 + LeapDay;}
    if (LeapDay > Shuoshi_HB){LeapDay = LeapDay - Shuoshi_HB;}
    //------------------------------------
    // Reuse Shoushi method again, no more integration with HouBian if the following steps are used
    LeapDay = fmod((total_days + Runying_Sh +(int)(abs(total_days))*Shuoshi_HB),Shuoshi_HB);
    RefMoonDay = Win_Sh - LeapDay;
    //=========================================
    // Use HouBian steps to simulate MidMoon
    //=========================================
    double SumDay_HB =(calculated_year - 1723)*YearDays_HB;
    double Win_HB = fmod((SumDay_HB + Qiying_HB +(int)(abs(SumDay_HB))*60),60);
    double UseDays = SumDay_HB +(Qiying_HB -(int)Qiying_HB)-(Win_HB -(int)Win_HB);
     
    double NetMoonDay_HB = UseDays - Shuoying_HB;
    double OffMoonDay_HB = fmod(NetMoonDay_HB, Shuoshi_HB);
    if (OffMoonDay_HB < 0){OffMoonDay_HB = Shuoshi_HB + OffMoonDay_HB;}
    //-----------------
    double Ch_Shuoying_Sh = fmod(Itotal_days - OffMoonDay_HB, Shuoshi_HB);
    if ((calculated_year == 1628)&(MonthNum == 0))
    {
    printf("\n\t=============================================================================\n");
    cout << "\tcalculated_year = " << calculated_year << "\tCh_Shuoying_Sh = " << Ch_Shuoying_Sh << endl;
    double LeapDay_Old = fmod((total_days + 20.2050 + int(abs(total_days))*29.530593),29.530593);
     
    double OffMoonDay_Xu = fmod(NetMoonDay_Sh, 29.530593);
    if (OffMoonDay_Xu < 0){OffMoonDay_Xu = 29.530593 + OffMoonDay_Xu;}
     
    double RefMoonDay_Xu = 60 + RefDays - OffMoonDay_Xu;
    double LeapDay_Xu = Win_Sh - RefMoonDay_Xu;
    if (LeapDay_Xu < 0){LeapDay_Xu = 60 + LeapDay_Xu;}
    if (LeapDay_Xu > 29.530593){LeapDay_Xu = LeapDay_Xu - 29.530593;}
     
    printf("\t\tLeapDay_Old = %3.6f\tLeapDay = %3.6f\tLeapDay_Xu = %3.6f",LeapDay_Old, LeapDay,LeapDay_Xu);
    printf("\n\t\tRefMoonDay(Old - New)=(55.06 - Qiying_Sh)-(LeapDay_Old - LeapDay)= %3.6f",(55.06 - Qiying_Sh)-(LeapDay_Old - LeapDay));
    printf("\n\t\t//RefMoonDay(Old - Xu)=(55.06 - Qiying_Sh)-(LeapDay_Old - LeapDay_Xu)= %3.6f",(55.06 - Qiying_Sh)-(LeapDay_Old - LeapDay_Xu));
    printf("//\n\t\tQiying(Old - New)=(55.06 - Qiying_Sh)= %3.6f",(55.06 - Qiying_Sh));
    printf("\n\t\tRefMoon(Old - New)=(13.0205 - Zhuanying_Sh)-(LeapDay_Old - LeapDay)= %3.6f",(13.0205 - Zhuanying_Sh)-(LeapDay_Old - LeapDay));
    printf("\n\t\tRefEcl(Old - New)=(26.0388 - Jiaoying_Sh)-(LeapDay_Old - LeapDay)= %3.6f",(26.0388 - Jiaoying_Sh)-(LeapDay_Old - LeapDay));
     
    printf("\n\t=============================================================================\n");
    }
     
    //-----------------
    double SumMonth = MonthNum - 1;
    if (SumMonth < 0){SumMonth = 0;}
     
    double UseMoonDay = Shuoshi_HB - OffMoonDay_HB;
    double YearsMoon = fmod(UseDays* 47435.0234086, 1296000)/3600;
    double MoonYearBase = YearsMoon +(176 + 27.0/60 + 48.0/3600 + 53.0/216000);
    double MonthsMoon = (UseMoonDay + SumMonth*Shuoshi_HB)*47435.0234086/3600;
    double MidMoon = fmod(MoonYearBase + MonthsMoon, 360);
    //=========================================
    // Use HouBian steps to simulate MaxMoon
    //=========================================
    // 求積日最高平行
    double UseMaxMoon = fmod(UseDays * 401.070226, 1296000)/3600;
    // 求最高年根
    double MaxYearBase = UseMaxMoon +(241 + 15.0/60 + 45.0/3600 + 38.0/216000);
    // 求最高日數
    double MaxDay = (UseMoonDay + SumMonth*Shuoshi_HB)* 401.070226/3600;
    // 求最高平行
    double MaxMoon =fmod(MaxYearBase + MaxDay, 360);
    if(MaxMoon < 0){MaxMoon = 360 + MaxMoon;}
    //-----------------------------------------
    double ReqMoon_HB = MidMoon - MaxMoon;
    if (ReqMoon_HB < 0){ReqMoon_HB = 360 + ReqMoon_HB;}
     
    //----------------
    // Step 2:
    double BaseSun = HalfYear - LeapDay; // check comparison for RSunYel
    //--------------------------------------------------------------------------------------
    // Shoushi drift problems referring to base year 1628 from Adam Schall 200 eclipse table
    // calculated data from http://ideone.com/BlkMI
    // for MoonDay = -(0.005499/347) => approx -0.0000158473
    // for sun = -(5.99089/347) => -0.0172648
    // for moon = (0.162147/347) => 0.000467281
    // for eclipse = (0.0122486/347) => 0.0000352987
    //rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
    // Update Ref_sun from HouBian MinSun for Shoushi BaseSun reference
    // ----------------------------------------------------------------
    // 求日數
    double BaseMoonDay = Shuoshi_HB - OffMoonDay_Sh;
    double DayNumber = fmod((BaseMoonDay +(MonthNum-1)*Shuoshi_HB)* 3548.3290897/3600, 360);
    // 求積年之行
    double YearsSun = (calculated_year - BaseYear)* 62.9975/3600;
    // 求日數之行
    double DaySun = DayNumber * 0.17248/3600;
    double YearsSun_Off = -7.734693056;
    // 求最卑平行
    double MinSun360 = YearsSun + DaySun +(8 + 7.0/60 + 32.0/3600 + 22.0/216000)+ YearsSun_Off;
    double MinSun = MinSun360 * YearDays/360;
    // 求引數
    double RefSun = BaseSun - MinSun - 2.43;
    //rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr
    double RefMoon = fmod((total_days + Zhuanying_Sh - LeapDay + int(abs(total_days))* Zhuanzhong),Zhuanzhong);
    double RefEcl = fmod((total_days + Jiaoying_Sh - LeapDay + int(abs(total_days))*Jiaozhong), Jiaozhong);
     
    //----------------
    // Step 3:
    double ReqEcl = fmod(((MonthJiao * MonthNum)+ RefEcl),Jiaozhong);
    double ReqEcl360 = fmod(ReqEcl * 360/Jiaozhong + 180, 360);
     
    double ReqMoonDay = fmod((RefMoonDay + Shuoshi_HB * MonthNum),60);
     
    double ReqSun = RefSun +(Shuoshi_HB * MonthNum);
    ReqSun = fmod(ReqSun, YearDays);
     
    double ReqSun360 = fmod(ReqSun * 360/YearDays + 180, 360);
    double e = 0.0167;
    double SunX_Th = 180/pi *(2 *e* sin(ReqSun360 *pi/180)+ 1.25 * e*e * sin(2*ReqSun360 *pi/180));
    double SFactor = 0.082 *(MoonMeanSpeed + 1); // = 1.1782375
     
    double SunX360 = SunX_Th * SFactor;
    double SunX = SunX360 * YearDays/360; // Step 7 include Shoushi SunX, just comment there if here is used for SunX
    double RSunYel = ReqSun360 + SunX_Th + MinSun360;
     
    double BaseMoon = fmod(RefMoon + MonthMoon * MonthNum, Zhuanzhong);
    double BaseMoon360 = fmod(BaseMoon * 360/Zhuanzhong + 180, 360);
    //----------------
    // Step 4:
    double ReqEcl_angle = ReqEcl * MoonMeanSpeed;
    //----------------
    // Step 5:
    double ChSun = ReqSun;
    if (ReqSun > HalfYear){ChSun = ReqSun - HalfYear;};
    //----------------
    // Step 6:
    double UseSun;int SunStatus;
    year.checkSunStatus(HalfYear, ReqSun, UseSun, SunStatus);
    //-----------------
    // Step 7:
    int IUseSun = int(UseSun);
    double SunAdd, SunSum;
    // year.get_SunX(SunStatus,UseSun,IUseSun,SunAdd, SunSum, SunX); // Step 3 also include SunX, just comment here if there is used
     
     
    // 求正交平均
    double PosExtra = -570 *SunX_Th/6973;
    double PosX360 = PosExtra * SFactor;
    double PosX = PosX360 * YearDays/360;
     
    //^^^^^^^^^^^^^^(Convert Shoushi ReqEcl as SunPos)^^^^^^^^^^
    double SunPos = (ReqEcl - Jiaozhong/2)*360/Jiaozhong - PosExtra + SunX_Th;
    if (SunPos < 0){SunPos = SunPos + 360;}
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     
    double UsePos = RSunYel - SunPos;
     
    // 求正交實均
    double SunPosReal = 180/pi *atan(56.0/59 *tan(SunPos * pi/180));
    if ((SunPos > 90)&(SunPos < 270)){SunPosReal = SunPosReal + 180;}
    if (SunPos > 270){SunPosReal = SunPosReal + 360;}
     
    // 正交實均
    double PosRealAdd = SunPos - SunPosReal;
     
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    double PosRX360 = PosRealAdd * SFactor;
    double PosRX = PosRX360 * YearDays/360;
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     
    // 求正交實行
    double PosReal = UsePos + PosRealAdd;
    double MoonPos = RSunYel - PosReal; // same as MoonPos = SunPos - PosRealAdd
    if (MoonPos < 0){MoonPos = MoonPos + 360;}
    //----------
    double YelWh = 5 + 17.0/60 + 20.0/3600;
    double YMoonPos = 180/pi * atan(cos(YelWh * pi/180)* tan(MoonPos * pi/180));
    if ((MoonPos > 90)&(MoonPos < 270)){YMoonPos = YMoonPos + 180;}
     
    double YelD = YMoonPos - MoonPos;
    if(YelD < -350){YelD = YelD + 360;}
    //-------------
    // Step 8:
    double SolarEclipse_angle;int Front = 0;
    year.get_SolarEclipse_angle(SunStatus,ReqEcl_angle,SunX, SolarEclipse_angle, Front);
    if (SolarEclipse_angle < 7){SolarEclipse_angle = SolarEclipse_angle + 363.7934196;}
     
    double SolEA = SolarEclipse_angle - PosX - PosRX;
    // if(NS_f < 0){SolEA = SolarEclipse_angle - NS_Hu/60;}
     
    double SolEA360 = fmod(SolEA + 363.7934196/2, 363.7934196)* 360/363.7934196;
    //---------------
     
    double LatYel = 180/pi *asin(sin(YelWh *pi/180)*sin(MoonPos *pi/180));
    LatYel = 180/pi *asin(sin(YelWh *pi/180)*sin(SolEA360 *pi/180));
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    // Convert Shoushi ReqMoon to consider Ee_o
    //---------------------------------------------------------------
    double OMoon360 = BaseMoon360;
    double OMoon = fmod(OMoon360 + 180,360)*Zhuanzhong/360;
    //------------------------------
    // apply Earth Center Offset for Moon adjustment
    double Ee_o = 0;
    if (cos(OMoon360 * pi/180)< 0){Ee_o = 0;}
    double y_scale = 1;
    double x_cir = cos(OMoon360 * pi/180);
    double y_cir = sin(OMoon360 * pi/180);
    double r_elip = 1/sqrt(x_cir*x_cir + y_cir*y_cir/(y_scale*y_scale));
    double x_o = r_elip * x_cir;
    double y_o = r_elip * y_cir;
     
    double EMoon360 = 180/pi *atan(y_o/(x_o - Ee_o));
    if ((OMoon360 > 90) & (OMoon360 < 270)){EMoon360 = 180 + EMoon360;}
    if (OMoon360 > 270){EMoon360 = 360 + EMoon360;}
    if ((OMoon360 < 90) & (EMoon360 < 0)){EMoon360 = 180 + EMoon360;}
    //------------------------------
    double MOff = EMoon360 - OMoon360;
    double EMoon = fmod((EMoon360 + 180)*Zhuanzhong/360, Zhuanzhong);
     
    double Em0_Off = -0.031;if (sin(EMoon360 *pi/180)< 0){Em0_Off = 0.031;}
    double Em1_Off = -0.06;if (sin(EMoon360 *pi/180)< 0){Em1_Off = -0.06;}
     
    double Em0 = 1.5*(-YelD + Em0_Off); if (sin(EMoon360 *pi/180)< 0){Em0 = 1.5*(YelD + Em0_Off);}
    double Em1 = 1.5*(YelD + Em1_Off); if (sin(EMoon360 *pi/180)< 0){Em1 = 1.5*(YelD + Em1_Off);}
     
    double MF = Em1;
    if (cos(EMoon360 *pi/180)> 0){MF = Em0;}
    MF = 0;
    double    ReqMoon = EMoon + MF;
    double ReqMoon360 = fmod(ReqMoon * 360/Zhuanzhong + 180, 360);
    //RRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
    //-------------
    // Step 9:
    int MoonStatus = 0;double UseMoon = 0, MoonLL, MoonAdd, SoD, moon_x12_2, MoonSolar;
    year.get_UseMoon(ReqMoon,UseMoon,SoD,moon_x12_2, MoonSolar, MoonStatus, MoonLL, MoonAdd);
    //-------------
    // Step 10:
    double MoonSum, MoonX, MoonSp;
    year.get_MoonX(MoonStatus, MoonLL, MoonAdd, MoonSolar, MoonSum, MoonX, MoonSp);
    //--------------
    // Step 11:
    double SunXS = -abs(SunX);
    if (SunStatus > LagEnd){SunXS = abs(SunX);}
     
    double MoonXS = -abs(MoonX);
    if (MoonStatus > LagEnd){MoonXS = abs(MoonX);}
     
    double SunMoonX = SunXS - MoonXS;
    double SunMoonT = SunMoonX * 0.082/MoonSp;
    //--------------
    double RSunEnd = RSunYel + SunMoonT * 360/YearDays;
     
    double MoonT24 = SunMoonT * 24;
    //------------------------------
    double MoonX360 = MoonXS * 360/YearDays;
    double UseRMoon = fmod(MidMoon + SunX_Th - SunX360 + MoonX360, 360);
    double RMoonEnd = fmod(UseRMoon + SunMoonT *(MoonSp/0.082 + 1)*360/YearDays, 360);
    //------------------------------
    double SunMoonXS = SunMoonX;
    int SunStatusS = SunStatus;
    int MoonStatusS = MoonStatus;
    //------------
    // Step 12:
    double MDay0 = ReqMoonDay - (int)ReqMoonDay;
    double MDay0_24 = MDay0 * 24;
     
    double MDayT = MDay0 + SunMoonT;
    if(MDayT < 0){MDayT = 1 + MDayT;}
    if(MDayT > 1){MDayT = MDayT - 1;}
    double MDayT_day = int(MDayT);
    double MDayT_hour = MDayT - int(MDayT);
    double MDayT_24hour = MDayT_hour * 24;
    //----------------------
    // Step 13: Shoushi observed_timeS just for comparison
    double time_from_noon = (MDayT - int(MDayT)) - 0.5;
    double observed_timeS = (0.5 - abs(time_from_noon))* (time_from_noon)/0.96;
    //----------------------
     
    int SeeTimeTable[][19]
    = {
    //h_deg-120 -105 -90 -75 -60 -45 -30 -15 0 15 30 45 60 75 90 105 120 <--
    //Gon h20 h19 h18 h17 h16 h15 h14 h13 h12 h11 h10 h9 h8 h7 h6 h5 h4 Gon
    //--------------------------------------------------------------------------------------------
    {9, -61, -72, -81, -85, -85, -78, -61, -34, -0, 34, 61, 78, 85, 85, 81, 72, 61, 9},
    {10, -51, -61, -68, -70, -66, -54, -32, -2, 33, 63, 84, 95, 99, 96, 90, 80, 67, 8},
    {11, -40, -49, -55, -55, -50, -37, -14, 15, 48, 75, 93, 103, 106, 103, 96, 86, 74, 7},
    {0, -33, -42, -48, -50, -46, -35, -15, 13, 44, 72, 92, 103, 108, 106, 100, 91, 80, 6},
    {1, -34, -44, -52, -55, -54, -45, -28, -3, 29, 60, 84, 98, 105, 105, 100, 92, 81, 5},
    {2, -45, -56, -64, -69, -69, -62, -46, -20, 13, 46, 73, 90, 97, 98, 94, 86, 75, 4},
    {3, -61, -72, -81, -85, -85, -78, -61, -34, 0, 34, 61, 78, 85, 85, 81, 72, 61, 3},
    //---------------------------------------------------------------------------------------------
    //Gon h4 h5 h6 h7 h8 h9 h10 h11 h12 h13 h14 h15 h16 h17 h18 h19 h20 Gon
    };
    //-->
     
    double degree = fmod(RSunEnd + 270, 360);
    double Gon = degree/30.0;
    double Hour = MDayT_hour * 24;
     
    int LRow = 9;
    int RRow = 9;
    if (fmod(Gon + 3,12.0) < 6){LRow = (int)(fmod((int)Gon + 3, 12.0));}
    if (fmod(Gon + 3,12.0) > 5){RRow = (int)(fmod(9 - (int)Gon, 12.0));}
     
    int TableTime = 0;
    int LHour = 0;
    double t0 = 0;
    double t1 = 0;
    double SeeT = 0;
     
    if (LRow < 6)
    {
    LHour = (int)Hour - 3;
    TableTime = SeeTimeTable[LRow][LHour];
    t0 = TableTime +(SeeTimeTable[LRow][LHour+1] - TableTime)*(Hour -(int)Hour);
     
    TableTime = SeeTimeTable[LRow+1][LHour];
    t1 = TableTime +(SeeTimeTable[LRow+1][LHour+1] - TableTime)*(Hour -(int)Hour);
    }
     
    int RHour = 0;
    if (LRow > 5)
    {
    if (RRow < 7)
    {
    RHour = 21 - (int)Hour;
    TableTime = SeeTimeTable[RRow][RHour];
    t0 = TableTime +(SeeTimeTable[RRow][RHour-1] - TableTime)*(Hour -(int)Hour);
    t0 = -t0;
     
    TableTime = SeeTimeTable[RRow-1][RHour];
    t1 = TableTime +(SeeTimeTable[RRow-1][RHour-1] - TableTime)*(Hour -(int)Hour);
    t1 = -t1;
    }
    }
    SeeT = t0 + (t1 - t0)*(Gon -(int)Gon);
    double SeeHour = SeeT/60;
    double observed_time = SeeHour/24;
    double eclipseMax_hour = MDayT_hour + observed_time;
     
    //-------------------
    double eclipseMax_24hour = eclipseMax_hour * 24;
     
    // cout << "===============================================" << endl;
    // cout << " eclipseMax_24hour = " << eclipseMax_24hour << endl;
    // cout << "===============================================" << endl;
    // cout << endl;
    //----------------
    // Step 14:
    // Calculate half day hours
     
    double Sunrise_time
    = 2068.3 +(((0.122928 -((IUseSun-53)* 0.000608))*(IUseSun-1))/2)*IUseSun + 0.06 * IUseSun;
     
    double Sunset_time = 10000 - Sunrise_time;
     
    double HalfDayFan = Sunset_time - 5000;
    if (SunStatus == LagEnd){HalfDayFan = 5000 - HalfDayFan;}
    if (SunStatus == LeadStart){HalfDayFan = 5000 - HalfDayFan;}
    //----------------
    // Step 15:
    double Net_time_from_noon = time_from_noon + observed_time;
    Net_time_from_noon = abs(Net_time_from_noon)* 10000;
    //--------------
    // Step 16:
    double EclD = ReqSun + int(MDayT) + eclipseMax_hour;
     
    double EclSun = EclD - ReqMoonDay;
     
    double EclUseSun;
    int EclSunStatus;
    year.checkSunStatus(HalfYear, EclSun, EclUseSun, EclSunStatus);
    //--------------
    // Step 17:
     
    double Ecl_SunAdd, Ecl_SunSum, Ecl_SunX;
    int IEclUseSun = int(EclUseSun);
    year.get_SunX(SunStatus, EclUseSun,IEclUseSun,Ecl_SunAdd, Ecl_SunSum, Ecl_SunX);
    double EclSun360 = fmod(EclSun * 360/YearDays + 180, 360);
    double EclSunX_Th = 180/pi *(2 *e* sin(EclSun360 *pi/180)+ 1.25 * e*e * sin(2*EclSun360 *pi/180));
    double EclSunX360 = EclSunX_Th * SFactor;
    Ecl_SunX = EclSunX360 * YearDays/360;
    //--------------
    // Step 18:
     
    double MaxEclSun = 0;
    if (SunStatus < LeadStart){MaxEclSun = EclSun - Ecl_SunX;}
    if (SunStatus > LagEnd){MaxEclSun = EclSun + Ecl_SunX;}
    //--------------
    // Step 19:
     
    double Ecl_NS;
    year.checkSunStatus(HalfYear, MaxEclSun, Ecl_NS, SunStatus);
     
    double NS_X = 4.46 -((Ecl_NS * Ecl_NS)/1870);
    double NS_Sh = NS_X -(NS_X * Net_time_from_noon)/HalfDayFan;
    //----------------
    // Step 20:
     
    double Ecl_EW = MaxEclSun;
    if(Ecl_EW > HalfYear){Ecl_EW = Ecl_EW - HalfYear;}
     
    double EW_X =((HalfYear - Ecl_EW)* Ecl_EW)/1870;
     
    double EW_H =(EW_X * Net_time_from_noon)/2500;
    double EW_Sh = EW_H;
    if(EW_H > EW_X){EW_Sh = 2 * EW_X - EW_H;}
    //---------------
    // Step 21:
     
    int AfterNoonSign = 1;
    if (time_from_noon < 0){AfterNoonSign = -1;}
     
    switch(SunStatus)
    {
    case LagStart:
    NS_Sh = Front * NS_Sh;
    EW_Sh = -AfterNoonSign * Front * EW_Sh; break;
     
    case LagEnd:
    NS_Sh = -Front * NS_Sh;
    EW_Sh = -AfterNoonSign * Front * EW_Sh; break;
     
    case LeadStart:
    NS_Sh = -Front * NS_Sh;
    EW_Sh = AfterNoonSign * Front * EW_Sh; break;
     
    case LeadEnd:
    NS_Sh = Front * NS_Sh;
    EW_Sh = AfterNoonSign * Front * EW_Sh; break;
     
    default:
    cout << " no SunStatus" << endl;
    }
    //---------------------------
    // Step 22: Shoushi EclipseFracS not used here but repeat in Step 23
    double eclipse_ref_angle = 0;
    if (Front == -1){eclipse_ref_angle = 188.05 + NS_Sh + EW_Sh;}
    if (Front == 1){eclipse_ref_angle = 357.64 + NS_Sh + EW_Sh;}
     
    double postiveEclipse_angle = SolarEclipse_angle - eclipse_ref_angle;
    double SexEcl = Front * postiveEclipse_angle;
     
    double EclipseFracS = 0;
    double EclipseRef = 6;
    if (SexEcl < 0){EclipseRef = 8;}
     
    EclipseFracS = (EclipseRef - abs(SexEcl))/EclipseRef;
    // See Step 23 for EclipseFracS
    //---------------------------
     
    int Lat_LongTable[][19]
    = {
    //h_deg-120 -105 -90 -75 -60 -45 -30 -15 0 15 30 45 60 75 90 105 120 <--
    //Gon h20 h19 h18 h17 h16 h15 h14 h13 h12 h11 h10 h9 h8 h7 h6 h5 h4 Gon
    //--------------------------------------------------------------------------------------------
    {9, 10, 15, 20, 25, 27, 30, 35, 40, 42, 40, 35, 30, 27, 25, 20, 15, 10, 9},//Lat(min)
    {9, 0, 2, 0, 47, 47, 41, 28, 26, 25, 27, 28, 41, 47, 47, 0, 2, 1, 9},//Lat(sec)
    {9, 30, 35, 40, 41, 42, 39, 31, 17, 0, 17, 31, 39, 42, 41, 40, 35, 30, 9},//Long(min)
    {9, 0, 0, 0, 20, 17, 30, 58, 6, 0, 6, 58, 30, 17, 21, 0, 0, 0, 9},//Long(sec)
     
    {10, 32, 33, 34, 35, 36, 40, 41, 41, 38, 32, 26, 20, 16, 14, 14, 13, 12, 8},
    {10, 0, 0, 40, 33, 38, 26, 29, 24, 25, 36, 40, 51, 48, 39, 0, 0, 0, 8},
    {10, 0, 0, 0, 35, 33, 30, 19, 3, 13, 30, 40, 46, 46, 46, 47, 48, 49, 8},
    {10, 0, 0, 0, 7, 27, 8, 49, 35, 10, 43, 37, 30, 42, 37, 0, 0, 0, 8},
     
    {11, 36, 37, 38, 39, 40, 41, 39, 36, 29, 21, 16, 11, 9, 8, 7, 6, 5, 7},
    {11, 0, 0, 26, 37, 39, 29, 34, 30, 29, 44, 44, 53, 57, 48, 51, 0, 0, 7},
    {11, 32, 31, 30, 30, 29, 23, 12, 1, 21, 35, 43, 47, 49, 49, 48, 47, 46, 7},
    {11, 0, 0, 13, 14, 16, 22, 29, 27, 15, 2, 1, 50, 44, 45, 47, 0, 0, 7},
     
    {0, 39, 40, 41, 41, 40, 38, 35, 28, 21, 13, 9, 7, 6, 5, 5, 5, 4, 6},
    {0, 0, 0, 27, 28, 30, 31, 25, 36, 41, 56, 53, 55, 54, 57, 53, 0, 0, 6},
    {0, 28, 29, 30, 30, 28, 21, 13, 0, 15, 32, 41, 47, 49, 49, 48, 48, 47, 6},
    {0, 0, 0, 3, 5, 4, 11, 13, 36, 32, 7, 57, 51, 44, 47, 47, 0, 0, 6},
     
    {1, 38, 39, 41, 40, 38, 33, 27, 21, 13, 8, 7, 6, 8, 8, 9, 10, 11, 5},
    {1, 0, 47, 26, 28, 21, 30, 36, 40, 55, 46, 52, 56, 48, 52, 27, 40, 0, 5},
    {1, 26, 27, 28, 30, 31, 27, 19, 7, 10, 26, 37, 45, 49, 49, 48, 48, 47, 5},
    {1, 0, 33, 26, 15, 9, 7, 11, 13, 23, 11, 5, 49, 46, 57, 53, 13, 0, 5},
     
    {2, 35, 35, 36, 34, 30, 25, 18, 10, 9, 6, 7, 10, 13, 16, 17, 16, 17, 4},
    {2, 17, 7, 33, 31, 30, 39, 54, 18, 50, 57, 52, 48, 47, 10, 11, 46, 0, 4},
    {2, 27, 28, 29, 31, 34, 34, 27, 13, 3, 18, 34, 43, 46, 47, 46, 45, 45, 4},
    {2, 41, 53, 52, 54, 36, 12, 22, 29, 20, 20, 38, 22, 27, 27, 34, 34, 0, 4},
     
    {3, 26, 27, 27, 26, 21, 17, 13, 8, 6, 8, 13, 17, 21, 26, 27, 27, 26, 3},
    {3, 40, 15, 55, 42, 48, 45, 45, 52, 56, 52, 45, 45, 48, 42, 55, 15, 40, 3},
    {3, 39, 40, 41, 42, 43, 39, 31, 18, 0, 18, 31, 39, 43, 42, 41, 40, 39, 3},
    {3, 13, 20, 27, 29, 35, 29, 37, 21, 0, 38, 37, 29, 25, 39, 27, 20, 13, 3},
     
    //---------------------------------------------------------------------------------------------
    //Gon h4 h5 h6 h7 h8 h9 h10 h11 h12 h13 h14 h15 h16 h17 h18 h19 h20 Gon
    //-->
    };
     
    enum TRow{Lat_min, Lat_sec, Long_min, Long_sec};
     
    LRow = 9;
    RRow = 9;
    if (fmod(Gon + 3,12.0) < 6){LRow = (int)(fmod((int)Gon + 3, 12.0));}
    if (fmod(Gon + 3,12.0) > 5){RRow = (int)(fmod(9 - (int)Gon, 12.0));}
     
    double NS_0 = 0;
    double NS_1 = 0;
    double NS_01 = 0;
    double NS_N0 = 0;
    double NS_N1 = 0;
    double NS_N01 = 0;
     
    double EW_0 = 0;
    double EW_1 = 0;
    double EW_01 = 0;
    double EW_N0 = 0;
    double EW_N1 = 0;
    double EW_N01 = 0;
     
    LHour = 0;
    double NS_Hu = 0;
    double EW_Hu = 0;
     
    if (LRow < 6)
    {
    LHour = (int)Hour - 3;
    NS_0 = Lat_LongTable[LRow *4+Lat_min][LHour] + Lat_LongTable[LRow*4+Lat_sec][LHour]/60.0;
    NS_1 = Lat_LongTable[LRow *4+Lat_min][LHour+1] + Lat_LongTable[LRow*4+Lat_sec][LHour+1]/60.0;
    NS_01 = NS_0 + (NS_1 - NS_0)*(Hour -(int)Hour);
     
    NS_N0 = Lat_LongTable[(LRow+1)*4+Lat_min][LHour] + Lat_LongTable[(LRow+1)*4+Lat_sec][LHour]/60.0;
    NS_N1 = Lat_LongTable[(LRow+1)*4+Lat_min][LHour+1] + Lat_LongTable[(LRow+1)*4+Lat_sec][LHour+1]/60.0;
    NS_N01 = NS_N0 + (NS_N1 - NS_N0)*(Hour -(int)Hour);
    //--------------
    EW_0 = Lat_LongTable[LRow *4+Long_min][LHour] + Lat_LongTable[LRow*4+Long_sec][LHour]/60.0;
    EW_1 = Lat_LongTable[LRow *4+Long_min][LHour+1] + Lat_LongTable[LRow*4+Long_sec][LHour+1]/60.0;
    EW_01 = EW_0 + (EW_1 - EW_0)*(Hour -(int)Hour);
     
    EW_N0 = Lat_LongTable[(LRow+1)*4+Long_min][LHour] + Lat_LongTable[(LRow+1)*4+Long_sec][LHour]/60.0;
    EW_N1 = Lat_LongTable[(LRow+1)*4+Long_min][LHour+1] + Lat_LongTable[(LRow+1)*4+Long_sec][LHour+1]/60.0;
    EW_N01 = EW_N0 + (EW_N1 - EW_N0)*(Hour -(int)Hour);
    }
     
    RHour = 0;
    if (LRow > 5)
    {
    if (RRow < 7)
    {
    RHour = 21 - (int)Hour;
    NS_0 = Lat_LongTable[RRow *4+Lat_min][RHour] + Lat_LongTable[RRow*4+Lat_sec][RHour]/60.0;
    NS_1 = Lat_LongTable[RRow *4+Lat_min][RHour-1] + Lat_LongTable[RRow*4+Lat_sec][RHour-1]/60.0;
    NS_01 = NS_0 + (NS_1 - NS_0)*(Hour -(int)Hour);
     
    NS_N0 = Lat_LongTable[(RRow-1)*4+Lat_min][RHour] + Lat_LongTable[(RRow-1)*4+Lat_sec][RHour]/60.0;
    NS_N1 = Lat_LongTable[(RRow-1)*4+Lat_min][RHour-1] + Lat_LongTable[(RRow-1)*4+Lat_sec][RHour-1]/60.0;
    NS_N01 = NS_N0 + (NS_N1 - NS_N0)*(Hour -(int)Hour);
    //---------------------------------
    EW_0 = Lat_LongTable[RRow *4+Long_min][RHour] + Lat_LongTable[RRow*4+Long_sec][RHour]/60.0;
    EW_1 = Lat_LongTable[RRow *4+Long_min][RHour-1] + Lat_LongTable[RRow*4+Long_sec][RHour-1]/60.0;
    EW_01 = EW_0 + (EW_1 - EW_0)*(Hour -(int)Hour);
     
    EW_N0 = Lat_LongTable[(RRow-1)*4+Long_min][RHour] + Lat_LongTable[(RRow-1)*4+Long_sec][RHour]/60.0;
    EW_N1 = Lat_LongTable[(RRow-1)*4+Long_min][RHour-1] + Lat_LongTable[(RRow-1)*4+Long_sec][RHour+1]/60.0;
    EW_N01 = EW_N0 + (EW_N1 - EW_N0)*(Hour -(int)Hour);
    }
    }
    NS_Hu = NS_01 + (NS_N01 - NS_01)*(Gon -(int)Gon);
    EW_Hu = EW_01 + (EW_N01 - EW_01)*(Gon -(int)Gon);
    //=============
    // From HouBian
    // ------------
    // 求最高平均
    double MaxExtra = 1196 * SunX_Th/6973;
    // 求用最高
    double UseMax = MaxMoon + MaxExtra;
     
    // 求日距月最高
    double MaxSMoon = RSunYel - UseMax;
    if (MaxSMoon < 0){MaxSMoon = MaxSMoon + 360;}
    //mmmmmmmmmm
    // 所夾之角
    double UseAngle = 180 - fmod(MaxSMoon *2, 360);
    // 最高實均
    double MaxRealExtra
    = 180/pi *atan((117315 *sin(UseAngle *pi/180))/(550505 - 117315 *cos(UseAngle *pi/180)));
    //mmmmmmmmmm
     
    // 求本天心距地數(本時两心差)
    double C_Earth = 117315.0/1000000 *sin(MaxSMoon *2*pi/180)/sin(MaxRealExtra *pi/180);
    //=========
    // HouBian_Step 3 :
    // 推地平高下差及日月視徑第三
     
    // 求太陰距地
    double DistCos = cos(ReqMoon360 * pi/180)* 2 * C_Earth;
    double DistSin = sin(ReqMoon360 * pi/180)* 2 * C_Earth;
    double AddDistCos = 20 - DistCos;
    double DistRef = DistSin * DistSin/AddDistCos;
    double CalRef = (DistRef + AddDistCos)/2;
     
    // 月距地心數(太陰距地)
    double MoonToEarth = 20 - CalRef;
     
    //求日距地心數
    // 太陽實引
    double ReqRealSun = fmod(ReqSun360 + SunX360, 360);
    // 分股
    double SideCos = cos(ReqRealSun * pi/180)* 0.338;
    // 勾
    double SideSin = sin(ReqRealSun * pi/180)* 0.338;
    // 勾弦和
    double AddSideCos = 20 + SideCos;
    // 勾弦較
    double SideRef = SideSin * SideSin/AddSideCos;
    // 弦
    double BaseRef =(SideRef + AddSideCos)/2;
    // 日距地心數
    double SunToEarth = 20 - BaseRef;
     
    //=======
    // HouBian_Step 2 :
     
    // 一小時太陰白道實行
    double HourWhiteMoon = MoonSp/0.082 + 1; // simulate HouBian
    double HourRSunYel = 1; // simulate HouBian
     
    // 求斜距交角差
    double XA = 180/pi*atan(HourRSunYel*sin(YelWh*pi/180)/(HourWhiteMoon-HourRSunYel*cos(YelWh*pi/180)));
     
    // 求斜距黃道交角
    double XYelA = YelWh + XA;
    // 求食甚實緯
    double MaxLat = LatYel * cos(XYelA *pi/180);
    //^^^^^^^^^^
    double MaxMoonX =(3450.0 * 10/MoonToEarth)/60;
    double HighLow = MaxMoonX - 10.0/60;
     
    double SunSeeSemiDiameter =(966 * 10/SunToEarth)/60;
    double SunRSemiDiameter = SunSeeSemiDiameter - 15.0/60;
    double MoonSeeSemiDiameter =(940.5 * 10/MoonToEarth)/60;
    double NetDiameter = SunRSemiDiameter + MoonSeeSemiDiameter;
    //^^^^^^^^^
    double MaxSunYel = RSunEnd + observed_time/24;
    double MaxPhaseUseT = eclipseMax_hour;
    //=========
    // HouBian_Step 4 : 推食甚太陽黃赤經緯宿度及黃赤二經交角第四
    //-----------------
    // 求食甚太陽赤道經度
    double SprYel = MaxSunYel - 90;
    double WinYel = MaxSunYel;
    double MaxSunRed = 180/pi*atan(cos((23+29.0/60)*pi/180)*tan(SprYel*pi/180));
     
    double SprRed = MaxSunRed;
    if ((SprYel > 90)&(SprYel < 270)){SprRed = 180 + MaxSunRed;}
    if (SprYel > 270){SprRed = 360 - MaxSunRed;}
    //-----------------
    // 求食甚太陽赤道緯度
    double ESunLat = 180/pi*asin(sin((23+29.0/60)*pi/180)*sin(SprYel*pi/180));
    // 求太陽距北極
    double SunNPole = 90 - ESunLat;
     
    // 求黃赤二經交角
    double YelRedXA = 90-180/pi*atan(tan((90-(23 + 29.0/60))*pi/180)/cos(SprYel*pi/180));
    if (cos(SprYel*pi/180)< 0){YelRedXA=YelRedXA-180;}
     
    // 求黄白二經交角
    double YelWhXA = XYelA;
    if (cos(MoonPos * pi/180) < 0){YelWhXA = -XYelA;}
     
    // 求赤白二經交角
    double RedWhXA = YelRedXA + YelWhXA;
     
    //=========
    // HouBian_Step 5 : 又法 page(792-248)推食甚近時第五
     
    // 求用時太陽距午赤道度
    double T_12Red =(MaxPhaseUseT -(int)MaxPhaseUseT - 0.5)* 24 * 15;
    //-----------------
    // 求用時赤經高弧交角
     
    // 北極距天頂 = 90 -(Beijing Lat)
    double NPoleV = 50.08333333;
    // 距極分邊
    double T_12X=180/pi*atan(cos(T_12Red*pi/180)*tan(NPoleV*pi/180));
    // 距日分邊
    double T_12NP = SunNPole - T_12X;
    // 垂弧之正切線
    double T_12Arc = tan(T_12Red*pi/180)*sin(T_12X*pi/180);
    // 用時赤經高弧交角
    double URedXA = 180/pi*atan(T_12Arc/sin(T_12NP*pi/180));
    //---------------
    // 求用時太陽距天頂
    double UseSunHL = 180/pi*asin(sin(NPoleV*pi/180)*sin(T_12Red*pi/180)/sin(URedXA*pi/180));
     
    // 求用時白經高弧交角
    double UWhXA = URedXA + RedWhXA;
    // 求用時高下差
    double UseHL = HighLow*sin(UseSunHL*pi/180);
    // 求用時東西差
    double UseEW = sin(UWhXA*pi/180)*UseHL;
    double EW_f = UseEW/60;
    // 求用時南北差
    double UseNS = -cos(UWhXA*pi/180)*UseHL;
    double NS_f = UseNS/60;
     
    // 求用時視緯
    double UseSeeLat = MaxLat*60 + UseNS;
    //^^^^^^^^^^^^^^^
    double ESeeLat = UseSeeLat/60;
    double SunHalfD = SunRSemiDiameter/60;
    double addD = NetDiameter/60;
     
    double eclipseFrac =(addD - abs(ESeeLat))/(2* SunHalfD);
    //--------------------
    // Step 22:
    double RefEA_Sh = 0;
    if (Front == -1){RefEA_Sh = 188.05;}
    if (Front == 1){RefEA_Sh = 357.64;}
    double ChEA = SolarEclipse_angle - RefEA_Sh - PosX - PosRX;
    double NetEA = ChEA -(NS_Sh + EW_Sh);
    double SexEA = NetEA;
    if (Front == -1){SexEA = -1.0 * NetEA;}
    //--------------------
    // Step 23:
     
    double EARef = 6;
    if (SexEA < 0){EARef = 8;}
    EclipseFracS = (EARef - abs(SexEA))/EARef;
    //---------------------
    // Step 24: Calculate Eclipse begin time and end time
     
    double EclM = ReqMoon + SunMoonT;
     
    double EclMoonSp = 0; double EclMoonLL; int EclMoonStatus = 0;
    double EclUseMoon,EclSoD,Eclmoon_x12_2,EclMoonSolar,EclMoonAdd;
    year.get_UseMoon(EclM,EclUseMoon,EclSoD,Eclmoon_x12_2,EclMoonSolar,EclMoonStatus,EclMoonLL,EclMoonAdd);
     
    year.get_MoonX(EclMoonStatus, EclMoonLL, EclMoonAdd,EclMoonSolar, MoonSum, MoonX, EclMoonSp);
     
    double MoonSunSp = EclMoonSp - 0.082;
    //---------------------------------
    double relative_time_difference
    = (sqrt((20 - eclipseFrac * 10)* eclipseFrac * 10)* 57.40)/MoonSunSp;
     
    // Hui Hui method here
    // relative_time_difference
    //= 24*60*sqrt(addD*addD - ESeeLat*ESeeLat)/EclMoonS;
     
    double eclipseBegin_hour = eclipseMax_hour - relative_time_difference/10000;
    double eclipseBegin_24hour = eclipseBegin_hour * 24;
     
    double eclipseEnd_hour = eclipseMax_hour + relative_time_difference/10000;
    double eclipseEnd_24hour = eclipseEnd_hour * 24;
    //----------------------------------
    double MidEclipse_time
    = (sqrt((20 - EclipseFracS * 10)* EclipseFracS * 10)* 57.40)/MoonSunSp;
     
    double eclipseBegin_hourS = eclipseMax_hour - MidEclipse_time/10000;
    double eclipseBegin_24hourS = eclipseBegin_hourS * 24;
     
    double eclipseEnd_hourS = eclipseMax_hour + MidEclipse_time/10000;
    double eclipseEnd_24hourS = eclipseEnd_hourS * 24;
    //------------------------------------
    if ((calculated_year == 1617)||(calculated_year == 1620)||(calculated_year == 1623))
    {
    // LunStep 3:
    double LunSun = fmod(ReqSun + Shuoshi_HB/2, YearDays);
    double	LunEcl = fmod(ReqEcl + Shuoshi_HB/2, Jiaozhong);
    double	LunDay = fmod(ReqMoonDay + Shuoshi_HB/2, 60);
    double	LunMoon = fmod(ReqMoon + Shuoshi_HB/2, Zhuanzhong);
     
    // LunStep 4:
    //-------------
    // 求交常交定度
    // 置經朔望入交泛日及分秒，以月平行度乘之，為交常度(LunEclA)；
    // 以盈縮差盈加縮減之，為交定度。
    //-------------
    double LunEclA = LunEcl * MoonMeanSpeed;
    // LunStep 6:
    double LUseSun; int LSunStatus;
    year.checkSunStatus(HalfYear, LunSun, LUseSun, LSunStatus);
    // LunStep 7:
    int ILUseSun =(int)LUseSun; double LSunAdd,LSunSum, LSunX;
    year.get_SunX(LSunStatus,LUseSun,ILUseSun,LSunAdd,LSunSum, LSunX);
    //-----------------------------
    double LunSun360 = fmod(LunSun * 360/YearDays + 180, 360);
    double LSunX_Th = 180/pi *(2 *e* sin(LunSun360 *pi/180)+ 1.25 * e*e * sin(2*LunSun360 *pi/180));
    double LSunX360 = LSunX_Th * SFactor;
    LSunX = LSunX360 * YearDays/360;
    //-----------------------------
    // LunStep 9:
    double LUseMoon,LSoD,Lmoon_x12_2,LMoonSolar,LMoonLL,LMoonAdd; int LMoonStatus;
    year.get_UseMoon(LunMoon,LUseMoon,LSoD,Lmoon_x12_2,LMoonSolar,LMoonStatus, LMoonLL,LMoonAdd);
    // LunStep 10:
    double LMoonSum,LMoonX, LMoonSp;
    year.get_MoonX(LMoonStatus,LMoonLL,LMoonAdd,LMoonSolar,LMoonSum,LMoonX, LMoonSp);
    // LunStep 11:
    double LSunXS = -abs(LSunX);
    if (LSunStatus > LagEnd){LSunXS = abs(LSunX);}
     
    double LMoonXS = -abs(LMoonX);
    if (LMoonStatus > LagEnd){LMoonXS = abs(LMoonX);}
     
    double LSunMoonX = LSunXS - LMoonXS;
    double LSunMoonT = LSunMoonX * 0.082/LMoonSp;
    // LunStep 12:
    double	ConjuncT = LunDay + LSunMoonT;
    if (ConjuncT < 0){ConjuncT = 1 + ConjuncT;}
     
    int ConjuncTDay = int(ConjuncT);
    double	ConjuncTHour = ConjuncT - int(ConjuncT);
    double	ConjuncT24 = ConjuncTHour * 24;
     
    // LunStep EclpseFraction:
    //----------------------------
    // 求交常交定度
    // 置經朔望入交泛日及分秒，以月平行度乘之，為交常度；
    // 以盈縮差盈加縮減之，為交定度(NetLunEclA)。
    //-----------------------------
    double NetLunEclA = LunEclA + LSunXS;
    //========================
    //求月食入陰陽曆去交前後度
    // 視交定度，在交中度(181.8967)已下，為陽曆；已上，減去交中，為陰曆。
    // 視入陰陽曆，在後准十五度半已下，為交後度；
    // 前准一百六十六度三十九分六十八秒已上，覆減交中，余為交前度及分。
    //==========================
    double SexLunEclA = abs(NetLunEclA);
    if (NetLunEclA > 181.8967){SexLunEclA = 181.8967 - NetLunEclA;}
     
    if (SexLunEclA > 166.3968){SexLunEclA = 181.8967 - SexLunEclA;}
    if (SexLunEclA < -166.3968){SexLunEclA = -181.8967 - SexLunEclA;}
     
    //============================================
    // simulate Xin Yunlu's result on SexLunEclA
    double LunEclA_Off = 0.343424;
    if (SexLunEclA > 0){SexLunEclA = SexLunEclA - LunEclA_Off;}
    if (SexLunEclA < 0){SexLunEclA = SexLunEclA + LunEclA_Off;}
    //=============================================
     
     
    //-------------------------------------------------
    //求月食分秒
    // 視去交前後度，
    // 不用南北東西差者。用減食限，不及減者不食。
    // 余如定法而一，為月食之分秒。
     
    double LunFraction =(13.05 - abs(SexLunEclA))/8.7;
    //--------------------------------------------------
     
    double ELMoon = LUseMoon + LSunMoonT;
    double ELUseMoon, ELSoD, ELmoon_x12_2, ELMoonSolar, ELMoonLL, ELMoonAdd;
    int ELMoonStatus;
    year.get_UseMoon(ELMoon,ELUseMoon,ELSoD,ELmoon_x12_2,ELMoonSolar,ELMoonStatus, ELMoonLL,ELMoonAdd);
     
    double ELMoonSum, ELMoonX, ELMoonSp;
    year.get_MoonX(ELMoonStatus,ELMoonLL,ELMoonAdd,ELMoonSolar,ELMoonSum,ELMoonX, ELMoonSp);
     
    double ELMoonSunSp = ELMoonSp - 0.082;
    double ELMoonMoveT =(sqrt((30 - LunFraction*10)*LunFraction*10)*49.20)/ELMoonSunSp;
     
    printf("%4d(%1d) ReqEcl = %5.2f\tLunEcl = %8.6f", calculated_year,MonthNum,ReqEcl,LunEcl);
    if (((calculated_year == 1617)&(MonthNum == 8))
    ||((calculated_year == 1620)&(MonthNum == 12))
    ||((calculated_year == 1623)&(MonthNum == 10)))
    {
    if (calculated_year == 1617){printf("(Xin YunLo data is 13.845663)\n");}
    cout << endl;
    printf("\tLunStep 3: LunSun = %5.3f\tLunDay = %5.3f\tLunMoon = %5.3f\n",LunSun,LunDay,LunMoon);
    printf("\tLunStep 4: LunEclA = %5.3f\n", LunEclA);
    printf("\tLunStep 6: LUseSun = %5.3f\tLSunStatus = %1d\n", LUseSun, LSunStatus);
    printf("\tLunStep 7: LSunAdd = %5.3f\tLSunSum = %5.3f\tLSunX = %5.3f\n",LSunAdd, LSunSum, LSunX);
    printf("\tLunStep 9: LUseMoon = %5.3f\tLSoD = %5.3f\tLmoon_x12_2 = %5.3f\tLMoonSolar = %5.3f\n",
    LUseMoon, LSoD,Lmoon_x12_2, LMoonSolar);
    printf("\t\t LMoonStatus = %1d\tLMoonLL = %5.3f\tLMoonAdd = %5.3f\n",LMoonStatus, LMoonLL,LMoonAdd);
    printf("\tLunStep 10: LMoonSum = %5.3f\tLMoonX = %5.3f\tLMoonSp = %5.3f\n",
    LMoonSum, LMoonX, LMoonSp);
    printf("\tLunStep 11: LSunXS = %5.3f\tLMoonXS = %5.3f\tLSunMoonX = %5.3f\tLSunMoonT = %5.3f\n",
    LSunXS,LMoonXS,LSunMoonX,LSunMoonT);
    printf("\tLunStep 12: ConjuncT = %5.3f\tConjuncTDay = %2d\tConjuncTHour = %5.3f\n",ConjuncT,ConjuncTDay,ConjuncTHour);
    printf("\t\t LunMaxPhase = ConjuncT24 = %5.8f", ConjuncT24);
    if (calculated_year == 1617){printf("(Xin YunLu's data is 3.1719864)\n\n");}
     
    printf("\n求交常交定度\n");
    printf(" 置經朔望入交泛日及分秒(LunEcl)，以月平行度(13.36875)乘之，為交常度(LunEclA)；\n");
    printf(" 以盈縮差(LSunXS)盈加縮減之，為交定度(NetLunEclA)。\n\n");
     
    printf("求月食入陰陽曆去交前後度\n");
    printf(" 視交定度，在交中度(181.8967)已下，為陽曆；已上，減去交中，為陰曆。\n");
    printf(" 視入陰陽曆，在後准十五度半已下，為交後度；\n");
    printf(" 前准一百六十六度三十九分六十八秒已上，覆減交中，余為交前度及分。\n");
     
    printf("\n\tLunStep EclpseFraction: NetLunEclA = LunEclA + LSunXS = %5.3f\n", NetLunEclA);
    printf("\t\t\t\t交中度 = 181.8967\n");
    printf("\t\t\t\tSexLunEclA = abs(NetLunEclA)\n");
    printf("\t\t\t\tif (NetLunEclA > 181.8967){SexLunEclA = 181.8967 - NetLunEclA}\n");
     
    printf("\t\t\tif (SexLunEclA > 166.3968){SexLunEclA = 181.8967 - SexLunEclA;}\n");
    printf("\t\t\tif (SexLunEclA < -166.3968){SexLunEclA = -181.8967 - SextLunEclA;}\n\n");
    printf("\t\t\t=============================================================\n");
    printf("\t\t\tsimulate Xin Yunlu's result on SexLunEclA\n");
    printf("\t\t\t\tLunEclA_Off = %3.6f", LunEclA_Off);
    printf("\n\t\t\t\tif (SexLunEclA > 0){SexLunEclA = SexLunEclA - LunEclA_Off;}\n");
    printf("\t\t\t\tif (SexLunEclA < 0){SexLunEclA = SexLunEclA + LunEclA_Off;}\n");
    printf("\t\t\t=============================================================\n");
    printf("\t\t\tSexLunEclA = %3.6f", SexLunEclA);
    if (calculated_year == 1617){printf("(Xin YunLu's data is -1.220395 < 181.8967)\n");}
     
    printf("\n求月食分秒\n");
    printf(" 視去交前後度，\n");
    printf(" 不用南北東西差者。用減食限，不及減者不食。\n");
    printf(" 余如定法而一，為月食之分秒。\n");
     
    printf("\n\t\t\tLunFraction =(13.05 - abs(SexLunEclA))/8.7 = %5.3f", LunFraction);
    if (calculated_year == 1617){printf("(Xin YunLu's data is 1.35969)");}
    if (calculated_year == 1620){printf("(Xin YunLu's data is 1.499)");}
     
    printf("\n\t\t\tELMoonMoveT/10000 = %2.6f", ELMoonMoveT/10000);
    if (calculated_year == 1617){printf("(Xin YunLu's data is 0.06689521)");}
    if (calculated_year == 1620){printf("(Xin YunLu's data is 0.069059813)");}
     
    printf("\n\t\t\tConjuncTHour = %2.6f",ConjuncTHour);
    if (calculated_year == 1617){printf("(Xin YunLu's data is 0.13216610)");}
    if (calculated_year == 1620){printf("(Xin YunLu's data is 0.0414598)");}
    cout << endl;
    }
    cout << endl;
    }
     
    int Print = 0;
    if (eclipseFrac < 0){eclipseFrac = EclipseFracS;}
    if (eclipseFrac > 0)
    {
    if (calculated_year >= eclipse_theo[index].year)
    {
    if (calculated_year > eclipse_theo[index].year)
    {eclipse_shoushi[index].eclipseFrac = -99;index = index + 1;}
     
    if (calculated_year == eclipse_theo[index].year)
    {
    if (MonthNum >= eclipse_theo[index].month)
    {
    Pindex = index;
    eclipse_shoushi[index].year = calculated_year;
    eclipse_shoushi[index].month = MonthNum;
     
    eclipse_shoushi[index].eclipseFrac = eclipseFrac;
    eclipse_shoushi[index].MoonSp = MoonSp;
    eclipse_shoushi[index].EclipseFracS = EclipseFracS;
    eclipse_shoushi[index].SunXS = SunXS;
    eclipse_shoushi[index].MoonXS = MoonXS;
     
    eclipse_shoushi[index].eclipseBegin = eclipseBegin_24hour;
    eclipse_shoushi[index].eclipseBeginS = eclipseBegin_24hourS;
    eclipse_shoushi[index].eclipseMax = eclipseMax_24hour;
    eclipse_shoushi[index].eclipseEnd = eclipseEnd_24hour;
    eclipse_shoushi[index].eclipseEndS = eclipseEnd_24hourS;
     
    eclipse_shoushi[index].SunStatus = SunStatus;
     
    eclipse_shoushi[index].observed_time = observed_time;
    eclipse_shoushi[index].HalfDayFan = HalfDayFan;
    eclipse_shoushi[index].ReqSun = ReqSun;
    eclipse_shoushi[index].ReqMoon = ReqMoon;
     
    eclipse_shoushi[index].Gon = Gon;
    eclipse_shoushi[index].MoonStatus = MoonStatus;
    eclipse_shoushi[index].SunMoonXS = SunMoonXS;
    eclipse_shoushi[index].MDayT_hour = MDayT_hour;
    eclipse_shoushi[index].observed_timeS = observed_timeS;
     
    eclipse_shoushi[index].SunStatusS = SunStatusS;
    eclipse_shoushi[index].MoonStatusS = MoonStatusS;
     
    index = index + 1;
    Print = 1;
    }
    }
    }
     
    if (Print == 1){//if_Print
    if (calculated_year == eclipse_theo[Pindex].year)
    {
    if (MonthNum >= eclipse_theo[Pindex].month)
    {
    if (calculated_year <= end_year)
    {
    printf("-------\n");
    printf("%4d(%1d) \t",calculated_year,MonthNum);
    printf("SprRed\tWinYel\tT_12Red\tYelRedXA+YelWhXA=RedWhXA[+]URedXA=UWhXA\tHighLow*sin(UseSunHL)=UseHL\n");
    printf("\t\t%3.2f\t%3.2f\t%3.2f\t%3.2f + %3.2f = %3.2f[+]%3.2f=%3.2f\t%3.2f*sin(%3.2f)=%3.2f\n",
    SprRed,WinYel,T_12Red,YelRedXA,YelWhXA,RedWhXA,URedXA,UWhXA,HighLow,UseSunHL,UseHL);
    printf("MidMoon-MaxMoon\tLeapDay ReqMDay\tReqSun()360\tReqMoon()360\tReqEcl");
    printf(" SunPos+UsePos=RSunYel UseRMoon RSunEnd/RMoonEnd\n");
    printf("%3.2f-%3.2f\t%3.2f\t%3.2f\t%3.2f(%1d)%3.2f",
    MidMoon,MaxMoon,LeapDay,ReqMoonDay, ReqSun,SunStatus,ReqSun360);
    printf("\t%3.2f(%1d)%3.2f\t%3.2f", ReqMoon,MoonStatus,ReqMoon360, ReqEcl);
    printf("\t%3.2f+%3.2f=%3.2f\t%3.2f\t%3.2f/%3.2f\n", SunPos,UsePos,RSunYel,UseRMoon, RSunEnd,RMoonEnd);
    printf("=%3.2f\n",ReqMoon_HB);
    printf("MinSun(360)\tT_12X\tT_12NP\tT_12Arc\tOMoon(360)\tSun_Th/SunXS/MoonXS\tEe_o\tEMoon360/MOff/MF\n");
    printf("%3.2f(%3.2f)\t%3.2f\t%3.2f\t%3.2f\t%3.2f(%3.2f)",MinSun,MinSun360,T_12X,T_12NP,T_12Arc,OMoon,OMoon360);
    printf("\t%3.2f/%3.2f/%3.2f \t%4.3f\t%3.2f/%3.2f/%3.3f\n",SunX_Th,SunXS,MoonXS,Ee_o,EMoon360, MOff,MF);
     
    printf("\tFrac\tMaxPh(MDayT)\tChEA\tSexEA\tWin_Sh\tWin_HB\n");
    printf("\t%4.3f\t%4.3f(%4.3f)",eclipseFrac,eclipseMax_24hour, MDayT_24hour);
    if (MoonLL >= 82){cout << "(>)";}
    printf("\t%3.2f\t%3.2f\t%3.2f\t%3.2f\n",ChEA,SexEA,Win_Sh,Win_HB);
    printf("MDay0_24 MoonT24 SeeT(min)\tXA+YelWh=XYelA\tLatYel\tMoonPos/YelD\tSolEA(360)\n");
    printf("%3.3f\t%3.3f\t%3.2f(%3.2f)\t%3.2f+%2.2f=%3.2f\t%3.2f\t%3.2f/%3.3f\t%3.2f(%3.2f)\n",
    MDay0_24,MoonT24,SeeHour,SeeT,XA,YelWh,XYelA,LatYel,MoonPos,YelD,SolEA,SolEA360);
    }
     
    printf("\tNS_Sh/EW_Sh\tNS_Hu/EW_Hu\tESunLat\tEW_f\tMaxLat+NS_f=ESeeLat\taddD\n");
    printf("\t%3.2f/%3.2f\t%3.2f/%3.2f\t%3.2f\t%3.2f\t%3.2f + %3.2f=%3.3f\t%3.3f\n\n",
    NS_Sh,EW_Sh, NS_Hu,EW_Hu,ESunLat, EW_f,MaxLat,NS_f,ESeeLat,addD);
    }
    }
    }//if_Print end
    }// if_1 end
    }
    }
    cout << endl;
    cout << "=====================================\n"
    << "\t\tdrift rate = offset/347 and 347 = 1628 - 1281(base year for Shoushi)\n"
    << "\t\tobserved_time is integrated with theorectical HuiHui calendar method table\n"
    << "\t\teclipse fraction is integrated from HouBian for comparison with Shoushi\n"
    << endl
     
    << "\tData record in Chongzhen Lishu(page 788-34):\n"
    << "\t\t65 fan late => 0.0065\n"
    << "\t\t6 days late => more than 6\n"
    << "\t\t2 degree late =>(2/365.2425)* 27.5546 => more than 0.150883864\n\n"
     
    << "\tShoushi drift from Adam Schall 200 eclipse table for year 1628\n"
    << "\t\tcalculated data from http://ideone.com/BlkMI\n"
    << "\t\tfor moon_days = -(0.005499/347) => approx -0.0000158473\n"
    << "\t\tfor sun = -(5.99089/347) => -0.0172648\n"
    << "\t\tfor moon =(0.162147/347) => 0.000467281\n"
    << "\t\tfor eclipse =(0.0122486/347) => 0.0000352987\n"
    << endl
    << "-------------------------\n"
    << "\t\tInverted Kepler elliptic model is implemented as :\n"
    << "\tReqSun360 = fmod(ReqSun * 360/YearDays + 180, 360)\n"
    << "\te = 0.0167\n"
    << "\tSunX_Th = 180/pi*(2 *e* sin(ReqSun360 *pi/180)+ 1.25* e*e * sin(2*ReqSun360 *pi/180))\n"
    << "\tSFactor = 0.082 *(MoonMeanSpeed + 1); // = 1.1782375\n"
    << "\tSunX360 = SFactor * SunX_Th\n"
    << "\tSunX = YearDays/360* SunX360\n"
    << "\tRSunYel = ReqSun360 + SunX_Th + MinSun360\n"
    << "\t=========================================\n"
    << endl
    << "\t\tConvert Shoushi ReqMoon to consider Ee_o\n"
    << "\tOMoon = BaseMoon\n"
    << "\tOMoon360 = fmod(OMoon * 360/Zhuanzhong + 180, 360)\n"
    << "\tif (OMoon360 < 0){OMoon360 = fmod(360 + OMoon360, 360);}\n\n"
     
    << "\t\tapply Earth Center Offset for Moon adjustment\n"
    << "\tEe_o = 0\n"
    << "\tif (cos(OMoon360 * pi/180)< 0){Ee_o = 0}\n"
    << "\ty_scale = 1\n"
    << "\tx_cir = cos(OMoon360 * pi/180)\n"
    << "\ty_cir = sin(OMoon360 * pi/180)\n"
    << "\tr_elip = 1/sqrt(x_cir*x_cir + y_cir*y_cir/(y_scale*y_scale))\n"
    << "\tx_o = r_elip * x_cir\n"
    << "\ty_o = r_elip * y_cir\n"
     
    << "\t\tEMoon360 = 180/pi *atan(y_o/(x_o - Ee_o))\n"
    << "\t\tif ((OMoon360 > 90)&(OMoon360 < 270)){EMoon360 = 180 + EMoon360;}\n"
    << "\t\tif (OReq_moon360 > 270){EMoon360 = 360 + EMoon360;}\n"
    << "--------------------\n"
    << "\tMOff = EMoon360 - OMoon360\n"
    << "\tEMoon = fmod((EMoon360 + 180)*Zhuanzhong/360, Zhuanzhong)\n\n"
     
    << "\tEm0_Off = -0.031\tif (sin(EMoon360 *pi/180)< 0){Em0_Off = 0.031}\n"
    << "\tEm1_Off = -0.06\tif (sin(EMoon360 *pi/180)< 0){Em1_Off = -0.06}\n"
    << "\tEm0 = 1.5*(-YelD + Em0_Off)\tif (sin(EMoon360 *pi/180)< 0){Em0 = 1.5*(YelD + Em0_Off)}\n"
    << "\tEm1 = 1.5*(YelD + Em1_Off)\tif (sin(EMoon360 *pi/180)< 0){Em1 = 1.5*(YelD + Em1_Off)}\n\n"
     
    << "\tMF = Em1\n"
    << "\tif (cos(EMoon360 *pi/180)> 0){MF = Em0}\n\n"
     
    << "\tReqMoon = EMoon + MF\n\n"
     
    << "\tMDay0 = ReqMoonDay -(int)ReqMoonDay\n\n"
     
    << "\t\tHuiHui observed time table is implemented as :\n"
    << "\tdegree = fmod(RSunEnd + 270, 360)\n"
    << "\tGon = degree/30.0\n"
    << "\tHour = MDayT_hour * 24\n"
    << endl
    << "int SeeTimeTable[][19]\n"
    << " = {\n"
    << "h_deg -120 -105 -90 -75 -60 -45 -30 -15 0 15 30 45 60 75 90 105 120 <--\n"
    << "Gon h20 h19 h18 h17 h16 h15 h14 h13 h12 h11 h10 h9 h8 h7 h6 h5 h4 Gon\n"
    << "-----------------------------------------------------------------------------------------------\n"
    << "{9, -61, -72, -81, -85, -85, -78, -61, -34, -0, 34, 61, 78, 85, 85, 81, 72, 61, 9},\n"
    << "{10, -51, -61, -68, -70, -66, -54, -32, -2, 33, 63, 84, 95, 99, 96, 90, 80, 67, 8},\n"
    << "{11, -40, -49, -55, -55, -50, -37, -14, 15, 48, 75, 93, 103, 106, 103, 96, 86, 74, 7},\n"
    << "{0, -33, -42, -48, -50, -46, -35, -15, 13, 44, 72, 92, 103, 108, 106, 100, 91, 80, 6},\n"
    << "{1, -34, -44, -52, -55, -54, -45, -28, -3, 29, 60, 84, 98, 105, 105, 100, 92, 81, 5},\n"
    << "{2, -45, -56, -64, -69, -69, -62, -46, -20, 13, 46, 73, 90, 97, 98, 94, 86, 75, 4},\n"
    << "{3, -61, -72, -81, -85, -85, -78, -61, -34, 0, 34, 61, 78, 85, 85, 81, 72, 61, 3},\n"
    <<"-----------------------------------------------------------------------------------------------\n"
    << "Gon h4 h5 h6 h7 h8 h9 h10 h11 h12 h13 h14 h15 h16 h17 h18 h19 h20 Gon\n"
    << "-->\n" << endl
     
    << "\tobserved_time = SeeT/(24*60)\n"
    << endl
    << "\teclipseMax_hour = MDayT_hour + observed_time\n\n"
    << "\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt\tt" << endl
    << "======================================================================================================================\n"
    << "Shoushi(year)(months)"
    << "\t\teclipseFraction \teclipseBegin\t\tMaxPhase\t\teclipseEnd" << endl;
    cout << "Theorectical(month/day)"
    << "\t\t\t(EclipseFracS)\t(eclipseBeginS)\t(observed_time x 24 x 60)\t(eclipse_endS)" << endl;
    cout << " HalfDayFan/ReqSun/ReqMoon"
    << "\t\t\t\t\t\t(observed_timeS x 24 x 60)" << endl
    << " SunXS(SunStatusS)/MoonSp" << endl
    << " MoonXS(MoonStatusS)/SunMoonXS" << endl
    << " Gon/MDayT" << endl;
    cout << "___________________________________________________________"
    << "___________________________________________________________" << endl
    << endl;
     
    int record;
    for (record = 0; record < index; record ++)
    {
    printf("%4d(%1d)",eclipse_shoushi[record].year,eclipse_shoushi[record].month);
    printf(" %4.2f",eclipse_shoushi[record].HalfDayFan);
    printf("/%2.1f/%2.1f", eclipse_shoushi[record].ReqSun, eclipse_shoushi[record].ReqMoon);
    printf("\t %5.4f(%5.4f)",eclipse_shoushi[record].eclipseFrac, eclipse_shoushi[record].EclipseFracS);
    cout << "\t " << eclipse_shoushi[record].eclipseBegin << "(" << eclipse_shoushi[record].eclipseBeginS << ")"
    << "\t " << eclipse_shoushi[record].eclipseMax << "(" << eclipse_shoushi[record].observed_time *24*60 << ")\t "
    << eclipse_shoushi[record].eclipseEnd << "(" << eclipse_shoushi[record].eclipseEndS << ")\n";
     
    cout << eclipse_theo[record].month << "/" << eclipse_theo[record].day;
    printf("\t%4.3f(%1d)/", eclipse_shoushi[record].SunXS, eclipse_shoushi[record].SunStatusS );
    printf("%4.3f ", eclipse_shoushi[record].MoonSp);
     
    printf("\t-)%5.4f", eclipse_theo[record].eclipseFrac);
    printf("\t\t-)%5.4f", eclipse_theo[record].eclipseBegin);
    printf("\t\t-)%5.4f", eclipse_theo[record].eclipseMax);
    printf("(%5.4f)", eclipse_shoushi[record].observed_timeS * 24 * 60);
    printf(" \t-)%6.4f\n", eclipse_theo[record].eclipseEnd);
     
    printf("\t%4.3f(%1d)/", eclipse_shoushi[record].MoonXS, eclipse_shoushi[record].MoonStatusS);
    printf("%4.3f ", eclipse_shoushi[record].SunMoonXS);
    cout << "\t--------------------------------------------------------------------------------------" << endl;
    printf("\t%3.2f/%3.2f", eclipse_shoushi[record].Gon, eclipse_shoushi[record].MDayT_hour * 24);
     
    printf("\t\t %5.4f",eclipse_shoushi[record].eclipseFrac - eclipse_theo[record].eclipseFrac);
    printf("(%5.4f)", eclipse_shoushi[record].EclipseFracS - eclipse_theo[record].eclipseFrac);
    printf("\t %5.4f", eclipse_shoushi[record].eclipseBegin - eclipse_theo[record].eclipseBegin);
    printf("(%5.4f)\t ",eclipse_shoushi[record].eclipseBeginS - eclipse_theo[record].eclipseBegin);
    printf("%5.4f\t\t", eclipse_shoushi[record].eclipseMax - eclipse_theo[record].eclipseMax);
    printf("%5.4f", eclipse_shoushi[record].eclipseEnd - eclipse_theo[record].eclipseEnd);
    printf("(%5.4f)\n\n", eclipse_shoushi[record].eclipseEndS - eclipse_theo[record].eclipseEnd);
    };
     
    cout << endl;
    return 0;
    }
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // 求正交平均
    // PosExtra = -570 *SunX_Th/6973;
    //======================================
    // Convert Shoushi ReqEcl as SunPos
    //======================================
    // 求日距正交
    // SunPos = (ReqEcl - Jiaozhong/2)* 360/Jiaozhong - PosExtra + SunX_Th;
    // if (SunPos < 0){SunPos = SunPos + 360;}
     
    // 求用正交
    // UsePos = RSunYel - SunPos;
     
    // MoonPos = RSunYel - PosReal
     
    // LatYel = 180/pi *asin(sin(YelWh *pi/180)*sin(MoonPos *pi/180))
    // Here use LatYel = 180/pi *asin(sin(YelWh *pi/180)*sin(SolEA360 *pi/180));
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // ESeeLat = UseSeeLat/60;
    // SunHalfD = SunRSemiDiameter/60;
    // addD = NetDiameter/60;
     
    // eclipseFrac =(addD - abs(ESeeLat))/(2* SunHalfD);
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // PosRX360 = PosRealAdd * SFactor;
    // PosRX = PosRX360 * YearDays/360;
     
    // SolEA = SolarEclipse_angle - PosX - PosRX
    // SolEA360 = fmod(SolEA + 363.7934196/2, 363.7934196)*360/363.7934196
    //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // EclipseFracS modified to include PosX and PosRX as :
    //--------------------------------------------
    // if (Front == -1){RefEA_Sh = 188.05}
    // if (Front == 1){RefEA_Sh = 357.64}
    // ChEA = SolarEclipse_angle - RefEA_Sh - PosX - PosRX
    // NetEA = ChEA -(NS_Sh + EW_Sh)
    // SexEA = NetEA
    // if (Front == -1){SexEA = -1*NetEA}
     
    // EARef = 6;
    // if (SexEA < 0){EARef = 8}
    // EclipseFracS = (EARef - abs(SexEA))/EARef
     
