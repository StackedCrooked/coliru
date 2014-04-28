#include <iostream>
#include <string>
#include <map>

struct UniqueNamesPair
{
    std::wstring substationName;
    std::wstring terminalName;

    bool operator< (const UniqueNamesPair & n) const
    {
        if ( substationName < n.substationName )
            return true;

        return terminalName < n.terminalName;
    }
};

struct UniqueIdsPair
{
    std::wstring substationId;
    std::wstring terminalId;
};

typedef std::map<UniqueNamesPair, UniqueIdsPair> GuidCache;

int main()
{
    UniqueNamesPair pn0 = { L"PS1", L"TERM1" };
    UniqueNamesPair pn1 = { L"PS2", L"TERM1" };
    UniqueNamesPair pn2 = { L"PS1", L"TERM0" };
    UniqueNamesPair pn3 = { L"PS1", L"TERM0" };
    
    UniqueIdsPair pi0 = { L"PS_ID1", L"TERM_ID1" };
    UniqueIdsPair pi1 = { L"PS_ID2", L"TERM_ID1" };
    UniqueIdsPair pi2 = { L"PS_ID1", L"TERM_ID0" };
    UniqueIdsPair pi3 = { L"PS_ID1", L"TERM_ID0" };

    GuidCache gc;
    gc[pn0] = pi0;
    gc[pn1] = pi1;
    gc[pn2] = pi2;
    gc[pn3] = pi3;
    
    for ( auto git: gc)
    {
        std::wcout << L"#" << std::endl;
        std::wcout << L"\t" << git->first.substationName << L": \t" << git->second.substationId << std::endl;
        std::wcout << L"\t" <<  git->first.terminalName << L": \t" << git->second.terminalId << std::endl;
    }
}
