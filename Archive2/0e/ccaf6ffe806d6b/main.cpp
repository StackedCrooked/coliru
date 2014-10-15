
#include <iostream>
#include <string>

using namespace std;
void function(string var, int flag);

int main(){
    function(R"!(
#include <iostream>
#include <string>

using namespace std;
void function(string var, int flag);

int main(){)!", 1);
    function(R"!(
    return 0;
}
void function(string var, int flag){
    const string startFunction = R"#(
    function(R"!()#";
    const string midFunction = { ')', '!', '"', ',', ' ', '\0' };
    const string endFunction = R"#();)#";

    if (flag == 1) {
        cout << var;
        cout << startFunction << var << midFunction << flag << endFunction;
    }
    else {
        cout << startFunction << var << midFunction << flag << endFunction;
        cout << var;
    }
}
)!", 0);
    return 0;
}
void function(string var, int flag){
    const string startFunction = R"#(
    function(R"!()#";
    const string midFunction = { ')', '!', '"', ',', ' ', '\0' };
    const string endFunction = R"#();)#";

    if (flag == 1) {
        cout << var;
        cout << startFunction << var << midFunction << flag << endFunction;
    }
    else {
        cout << startFunction << var << midFunction << flag << endFunction;
        cout << var;
    }
}
