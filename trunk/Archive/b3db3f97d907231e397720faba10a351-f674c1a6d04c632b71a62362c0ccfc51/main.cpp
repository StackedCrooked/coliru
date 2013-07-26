#include <iostream>
#include <string>

class Retrospective
{
    public:
    
    friend std::wostream& operator<<(std::wostream& output, const Retrospective& value);
    
    Retrospective() : 
    _text(L"==== [RETRO] Iteration 35 ===="
    L"\nLes actions precedentes")
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
    
    friend std::wostream& operator<<(std::wostream& output, const ActionImmediate& value);
    
    ActionImmediate() :
    _participant(4),
    _text(L"==== Actions immediates ! ====")
    {
        updateText(L"\nDeplacer l'heure de la stand up a 11h45", 3);
        updateText(L"\nAvoir les specs au meme endroit par : http://confluence/pages/viewpage.action?pageId=3736215 et http://confluence/pages/viewpage.action?pageId=9217693 quit a ecraser les anciennes", 3);
    }
    
    private:
    
    const int _participant;
    std::wstring  _text;
    
    void updateText(const std::wstring& action, int vote)
    {
        if (vote > (_participant>>1))
            _text+=action+L" [OK]";
        else
            _text+=action+L" [KO]";
    }
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

std::wostream& operator<<(std::wostream& output, const ActionImmediate& value) {
    return output << value._text.c_str();
}

int main()
{
    Retrospective retropective;
    JaimeEtJeSouhaiteContinuer jaime;
    JaimePasJaimeraiQueCelaEvolue jaimePas;
    ActionImmediate actionImmediate;
    
    std::wcout << retropective << std::endl << jaime << std::endl << jaimePas << std::endl << actionImmediate << std::endl;
    
    return 0;
}