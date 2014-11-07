#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <regex.h>

class A {
public:
    A(std::string sLabel) : _sLabel(sLabel) { }
    virtual ~A() throw() { }
    
    virtual void foo() = 0;
protected:
    std::string     _sLabel;
};

class B : public A {
public:
    B(std::string sLabel
    , std::string sMessage) : A(sLabel)
                            , _sMessage(sMessage) { }
    virtual ~B() throw() { }
    
    virtual void foo() = 0;
protected:
    std::string     _sMessage;
};

class C : public B {
public:
    C(std::string sLabel
    , std::string sMessage) : B(sLabel, sMessage) { }
    virtual ~C() throw() { }
    
    virtual void foo() {
        std::cout << "C: " << _sLabel << " M: " << _sMessage << std::endl;
        myFoo();
    }
    
    void myFoo() {
        std::cout << "***C: This is my foo" << std::endl;
    }
private:
    
};

class D : public B {
public:
    D(std::string sLabel
    , std::string sMessage) : B(sLabel, sMessage) { }
    virtual ~D() throw() { }
    
    virtual void foo() {
        std::cout << "D: " << _sLabel << " M: " << _sMessage << std::endl;
        myFoo();
    }
    
    void myFoo() {
        std::cout << "***D: This is my foo" << std::endl;
    }
private:
  
};

class E : public A {
public:
    E(std::string sLabel) : A(sLabel) { }
    virtual ~E() throw() { }
    
    virtual void foo() {
        std::string sOutput(_sLabel);
        std::transform(sOutput.begin(), sOutput.end(), sOutput.begin(), ::toupper);
        std::cout << "E: " << sOutput << std::endl;
        
        sOutput.assign(_sLabel);
        std::transform(sOutput.begin(), sOutput.end(), sOutput.begin(), ::tolower);
        std::cout << "E: " << sOutput << std::endl;
    }
private:
};

void executeCommand(A *a) {
    a->foo();
}

A *create(int iType) {
    switch(iType) {
    case 0:
        return new C("C Command", "Message is from C");
        break;
    case 1:
        return new D("D Command", "Message is from D");
        break;
    case 2:
        return new E("E Command");
        break;
    default:
        break;
    }
    
    return NULL;
}

bool checkRegExpression(const std::string& sPattern
                      , std::string& sTarget) {
    int     iRes;
    regex_t regex;    

    std::cout << "Checking RegExp <"
              << sPattern.c_str() << " | "
              << sTarget.c_str() << ">" << std::endl;
    
    iRes = regcomp(&regex, sPattern.c_str(), REG_EXTENDED);
    if(iRes) { 
        throw "Error. Wrong regular expression format.";
    }

    iRes = regexec(&regex, sTarget.c_str(), 0, NULL, 0);

    return iRes == 0;  
}

void tokenize(const std::string& str,
              std::vector<std::string>& tokens,
              const std::string& delimiters = " ") {
#if 0
    // Skip delimiters at beginning.
    //string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type lastPos = 0;
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    std::cout << "012345678901234567890" << std::endl;
    std::cout << str << "[" << str.length() << "]" <<std::endl;
    while (pos != std::string::npos && lastPos != std::string::npos) {
        std::cout << "[" << lastPos << "," << pos << "][" << (pos - lastPos) << "]" <<  str.substr(lastPos, pos - lastPos) <<  std::endl;
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = pos + 1; //str.find_first_not_of(delimiters, pos);
        
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
        
        if (pos == std::string::npos) {
            tokens.push_back("");
        }
        std::cout << "  [" << lastPos << "," << pos << "][" << (pos - lastPos) << "]" <<  str.substr(lastPos, pos - lastPos) <<  std::endl;
    }
#endif
    std::cout << "012345678901234567890" << std::endl;
    std::cout << str << "[" << str.length() << "]" <<std::endl;
    
    std::string::size_type iActualPos = 0;
    std::string::size_type iLastPos = 0;
    do {
        std::cout << "[" << iLastPos << "," << iActualPos << "][" << (iActualPos - iLastPos) << "]" <<  str.substr(iLastPos, iActualPos - iLastPos) <<  std::endl;
        iActualPos = str.find_first_of(delimiters, iLastPos);
        std::cout << "  [" << iLastPos << "," << iActualPos << "][" << (iActualPos - iLastPos) << "]" <<  str.substr(iLastPos, iActualPos - iLastPos) <<  std::endl;
        tokens.push_back(str.substr(iLastPos, iActualPos - iLastPos));
        if (iActualPos != (str.length() - 1)) {
            iLastPos =  iActualPos + 1;    
        }
        //iLastPos = str.find_first_not_of(delimiters, iActualPos);
        //std::cout << "  [" << iLastPos << "," << iActualPos << "][" << (iActualPos - iLastPos) << "]" <<  str.substr(iLastPos, iActualPos - iLastPos) <<  std::endl;
        std::cout << "  [" << iLastPos << "," << iActualPos << "][" << (iActualPos) << "]" <<  str.substr(iLastPos, iActualPos - iLastPos) <<  std::endl;
    } while(iActualPos != std::string::npos && iLastPos != std::string::npos);
}

int main(int argc, char *argv[]) {
#if 0
    A *c = create(0);
    A *d = create(1);
    A *e = create(2);
        
    executeCommand(c);
    executeCommand(d);
    executeCommand(e);
    
    delete c;
    delete d;
    delete e;
#endif

#if 0
    std::vector<std::string> vecTokens;
    std::string test = "AB,,CS";
    
    tokenize(test, vecTokens, ",");
    std::cout << vecTokens.size() << std::endl;
    
    std::vector<std::string>::iterator itr;
    for (itr = vecTokens.begin(); itr != vecTokens.end(); ++itr) {
        std::cout << *itr << (*itr).length() << std::endl;
    }
#endif   

    std::string sTest = "12341234";
    if (checkRegExpression("^-?[0-9]+.[0-9]+$"
                         , sTest)) {
        std::cout << "OK!!" << std::endl;
    } else {
        std::cout << "NOK!!" << std::endl;
    }
    
    std::map<std::string, std::string> mapTest;
    std::string sTest1 = "es";
    mapTest.insert(std::pair<std::string, std::string>("Test1", "Esto " + sTest1 + " una Prueba."));
    
    return 0;
}
