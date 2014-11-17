#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
#include <regex.h>
#include <ctime>
#include <unistd.h>
#includ <cstdio>

class A {
public:
    A(std::string sLabel) : _sLabel(sLabel)
                          , _initTime(time(NULL)) { }
    virtual ~A() throw() { }
    
    virtual void foo() = 0;
protected:
    std::string     _sLabel;
    std::time_t     _initTime;
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
        std::cout << "***C: This is my foo " << _initTime << std::endl;
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

enum Commands {
    COMMAND_ALPERABO            = 65, // = 'A';
    COMMAND_CONSBONO            = 66, // = 'B';
    COMMAND_BAPERABO            = 69, // = 'E';
    COMMAND_LOGICA_FIN          = 70, // = 'F';
    COMMAND_FICHPP17            = 72, // = 'H';
    COMMAND_ENVIO_SMS_CONT      = 73, // = 'I';
    COMMAND_SOLBONO5            = 76, // = 'L';
    COMMAND_CONPERABO           = 78, // = 'N';
    COMMAND_SLEEP               = 79, // = 'O';
    COMMAND_LOGICA_PATRON       = 80, // = 'P';
    COMMAND_RECARGA             = 82, // = 'R';
    COMMAND_ENVIO_SMS_FIN       = 83, // = 'S';
    COMMAND_COBRAR              = 84, // = 'T';
    COMMAND_LOGICA_PALABRA      = 87, // = 'W';
    COMMAND_ENVIO_WS_FIN        = 88, // = 'X';
    COMMANDS_SIZE
};

void createInstance(char cCommand) {
    std::cout << cCommand << "|" << COMMANDS_SIZE <<  std::endl;
    switch (cCommand) {
        case COMMAND_LOGICA_PATRON:        // = 'P';
            std::cout << "P" << std::endl;
            break;
        case COMMAND_LOGICA_PALABRA:       // = 'W';
            std::cout << "W" << std::endl;
            break;
        case COMMAND_ENVIO_SMS_CONT:       // = 'I';
            std::cout << "I" << std::endl;
            break;
        case COMMAND_RECARGA:              // = 'R'; 
            std::cout << "R" << std::endl;     
            break;  
        case COMMAND_COBRAR:               // = 'T';
            std::cout << "T" << std::endl;
            break;
        case COMMAND_CONSBONO:             // = 'B'; 
            std::cout << "B" << std::endl;   
            break;  
        case COMMAND_SOLBONO5:             // = 'L';
            std::cout << "L" << std::endl;
            break;
        case COMMAND_FICHPP17:             // = 'H';  
            std::cout << "H" << std::endl;
            break;      
        case COMMAND_CONPERABO:            // = 'N'; 
            std::cout << "N" << std::endl;
            break;             
        case COMMAND_ALPERABO:             // = 'A';
            std::cout << "A" << std::endl;
            break;
        case COMMAND_BAPERABO:             // = 'E';
            std::cout << "E" << std::endl;
            break;
        case COMMAND_ENVIO_SMS_FIN:        // = 'S';
            std::cout << "S" << std::endl;
            break; 
        case COMMAND_LOGICA_FIN:           // = 'F';
            std::cout << "F" << std::endl;
            break;
        case COMMAND_ENVIO_WS_FIN:         // = 'X'; 
            std::cout << "X" << std::endl;
            break;
        case COMMAND_SLEEP:                // = 'O';
            std::cout << "O" << std::endl;
            break;
        default:
            std::cout << "Fail!!!" << std::endl;
            break;
    }
}

class F {
public:
    F() { 
        std::cout << "Init F" << std::endl;    
    }
    
    virtual ~F() throw() {
        std::cout << "End F" << std::endl;
    }
    
    virtual void foo() {
        std::cout << "foo F" << std::endl;
    }
private:
    
};

class G : public F {
public:
    G() { 
        std::cout << "Init G" << std::endl;  
    }
    
    virtual ~G() throw() {
        std::cout << "End G" << std::endl;
    }
    
    virtual void foo() {
        std::cout << "Prev F" << std::endl;
        F::foo();
        std::cout << "Post F" << std::endl;
    }
private:
    
};
#if 0   
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
#if 0
    std::string sTest = "1234.1234";
    if (checkRegExpression("^-?[0-9]+\\.[0-9]+$"
                         , sTest)) {
        std::cout << "OK!!" << std::endl;
    } else {
        std::cout << "NOK!!" << std::endl;
    }
    
    std::map<std::string, std::string> mapTest;
    std::string sTest1 = "es";
    mapTest.insert(std::pair<std::string, std::string>("Test1", "Esto " + sTest1 + " una Prueba."));
#endif       
#if 0    
    createInstance('W');
    
    std::string sTest("Test12345");
    if (sTest.compare("Test12345") == 0) {
        std::cout << "OK!" << std::endl;    
    } else {
        std::cout << "NOK!" << std::endl;
    }
#endif
#if 0   
    std::vector<std::string> vecStrings;
    vecStrings.push_back("abc");
    vecStrings.push_back("def");
    vecStrings.push_back("fgh");
    
    if (std::find(vecStrings.begin(), vecStrings.end(), "abcd") != vecStrings.end()) {
        std::cout << "OK" << std::endl;
    } else {
        std::cout << "NOK" << std::endl;
    }
    
    C c1("test C1", "Message 1"); 
    c1.foo();
    sleep(5);
    C c2("test C2", "Message 2");
    c2.foo();
    sleep(10);
    C c3("test C3", "Message 3");
    c3.foo();
#endif

#if 0
    F *f = new G();
    f->foo();
    delete f;
    
#endif
    return 0;
}
#endif

class Test {
public:
    Test(int         iId
       , std::string sMessage) : _iId(iId)
                               , _sMessage(sMessage) { }
    virtual ~Test() throw() { }
    
    int getId() const {
        return _iId;
    }
    
    std::string getMessage() const {
        return _sMessage;
    }
private:
    int         _iId;
    std::string _sMessage;
};

Test* getTestById(std::vector<Test *>& vecTest
                , int iIndex) {
    for (unsigned int i = 0; i < vecTest.size(); i++) {
        if (vecTest[i]->getId() == iIndex) {
            return vecTest[i];
        }
    } 
    
    return NULL;
}
    
int main(int argc, char *argv[]) {
    std::vector<Test *> vecTest;
    vecTest.push_back(new Test(1, "1"));
    vecTest.push_back(new Test(2, "2"));
    vecTest.push_back(new Test(3, "3"));
    vecTest.push_back(new Test(4, "4"));
    vecTest.push_back(new Test(5, "5"));
    vecTest.push_back(new Test(6, "6"));
    vecTest.push_back(new Test(7, "7"));
    
    int iIndex = 7;
    std::string sMessage("");
    if (!getTestById(vecTest, 7)) {
        sMessage = "";
    } else {
        sMessage = getTestById(vecTest, 7)->getMessage();
    }
    
    std::cout << sMessage << std::endl;
    
    printf("%s, Comando [%s]", "Funcion::test", 'a');
    
    return 0;
}

