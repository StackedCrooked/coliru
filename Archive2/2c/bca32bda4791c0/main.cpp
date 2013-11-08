string code(string worth, int decalage) {
    string test = "";
    
    for (char wort : worth) {
    
        if (wort <= 'Z' && wort >= 'A') {
            char bst = wort + decalage;
    
            if (bst > 'Z') {
                bst = bst - 'Z'+('A'-1);
                test += bst;                
            }
        }
        else if (wort >= 'a' && wort <= 'z') {
            char bst  = wort + decalage;
            if (bst > 'z') {
                bst = bst - 'z' + ('a'-1);
                test += bst;
            }
        }
        else {
            test += wort;
        }
    
    }
    return test;
}