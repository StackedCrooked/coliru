    #include <string>
    #include <iostream>

    int main()
    {
        std::wstring newwd;
        setlocale(LC_ALL, "");
        std::wcout << "Enter greek word ";
        std::string wordgr;
        std::wgetline(std::wcin, wordgr);
        std::wcout << "The word is " << wordgr << "." << std::endl;
        newwd=wordgr.substr(2,1) ;
        std::wcout << "3rd letter is " << wordgr.substr(2,1) << " <" << std::endl;
        return 0;
    } 