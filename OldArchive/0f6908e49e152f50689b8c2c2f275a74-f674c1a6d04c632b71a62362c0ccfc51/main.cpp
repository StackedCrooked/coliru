#include <iostream>
#include <string>

class Retrospective
{
    public:
    
    friend std::wostream& operator<<(std::wostream& output, const Retrospective& value);
    
    Retrospective() : 
    _text(L"==== [RETRO] Itération 35 ===="
    L"\nLes actions précédentes")
    {}
    
    private:
    
    std::wstring  _text;
};

class JaimeEtJeSouhaiteContinuer
{
    
    public:
    
    friend std::wostream& operator<<(std::wostream& output, const JaimeEtJeSouhaiteContinuer& value);
    
    JaimeEtJeSouhaiteContinuer() : 
    _text(L"==== J'aime ====")
    {}
    
    private:
    
    std::wstring  _text;
};

class JaimePasJaimeraiQueCelaEvolue
{
    public:
    
    friend std::wostream& operator<<(std::wostream& output, const JaimePasJaimeraiQueCelaEvolue& value);
    
    JaimePasJaimeraiQueCelaEvolue() : 
    _text(L"==== J'aime pas ====")
    {}
    
    private:
    
    std::wstring  _text;
};

class ActionImmediate
{
    public:
    
    friend std::wostream& operator<<(std::wostream& output, const JaimePasJaimeraiQueCelaEvolue& value);
    
    JaimePasJaimeraiQueCelaEvolue() : 
    _text(L"==== J'aime pas ====")
    {}
    
    private:
    
    std::wstring  _text;
};



std::wostream& operator<<(std::wostream& output, const Retrospective& value) {
    return output << value._text.c_str();
}

std::wostream& operator<<(std::wostream& output, const JaimeEtJeSouhaiteContinuer& value) {
    return output << value._text.c_str();
}

std::wostream& operator<<(std::wostream& output, const JaimePasJaimeraiQueCelaEvolue& value) {
    return output << value._text.c_str();
}

int main()
{
    Retrospective retropective;
    JaimeEtJeSouhaiteContinuer jaime;
    JaimePasJaimeraiQueCelaEvolue jaimePas;
    ActionImmediate actionImmediate;
    
    std::wcout << retropective << std::endl << jaime << std::endl << jaimePas << std::endl;
    
    return 0;
}