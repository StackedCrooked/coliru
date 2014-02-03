#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <array>
#include <algorithm>
using namespace std;


string parse_date(string date, string format, array<string, 12> *month_names = NULL){
tm time_s;
    	if(month_names != NULL){
			const char *f = format.c_str();
			stringstream not_parse_plis;
			int replace_month_char = -1;
			int j = -1;
			int month_l = -1;
			for(int i=0;i<format.size();++i){
				if(f[i] == '%'){
					if(++i<format.size()){
						if(f[i] == '%')
							not_parse_plis << '%';
						else {
							int t = !not_parse_plis.str().empty()?(date.find(not_parse_plis.str(), j)):0;
							if(t>0){
								t += not_parse_plis.str().size();
								
							}
							j=t;
							
							cout <<j <<  " '" <<not_parse_plis.str()<<"' "<<endl;
							//cout<<"SS " << date.substr(j);
							//advance in date
							if(f[i] == 'm'){
								replace_month_char = j;
							} else {
								if(replace_month_char != -1 && month_l == -1)
									month_l = j - replace_month_char -not_parse_plis.str().size();
							}
							not_parse_plis.str("");
							
						}
					}
				} else
					not_parse_plis << f[i];
			}
			if(replace_month_char == -1 || month_l == -1)
				return "";
			cout << date.substr(replace_month_char, month_l)<<endl;
			stringstream ss;
			string mese = date.substr(replace_month_char, month_l);
			int n = std::distance(month_names->begin(), std::find(month_names->begin(), month_names->end(), mese));
			ss << date.substr(0, replace_month_char) << n << date.substr(replace_month_char+ month_l);
			date = ss.str();
		}
		if(strptime(date.c_str(), format.c_str(), &time_s)){
			return date.c_str()+" "+format.c_str();
		}
		stringstream ss;
		ss << time_s.tm_year << '/' << (time_s.tm_mon+1) << '/' << time_s.tm_mday << ' ' << time_s.tm_hour << ':' << time_s.tm_min << ':'<< time_s.tm_sec;
		return ss.str();
	}

int main(){
    array<string,12> mm = {{ "gennaio", "febbraio", "marzo" }}; 
    cout << parse_date("12 marzo 2013", "%d %m %Y", &mm) <<endl;
}

