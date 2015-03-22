#include <iostream>
using namespace std;
int encrypt()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    char text1[300];
    cout << "Enter message to encrypt: ";
    cin.getline ( text1, 300 );
    string pass = text1;
    char text2[300];
    cout << "Enter key: ";
    cin.getline ( text2, 300 );
    string phrase = text2;
    string decy = "";

    string orig = pass;
    string newPass = "";

    for( int a = 0, r = 0; newPass.length() < pass.length(); r++ )
        {
            if( pass[r] == ' ' )
                {
                    newPass += ' ';
                }
            else
                {
                    newPass += phrase[a];
                    a++;
                }
            if( a >= phrase.length() )
                {
                    a = 0;
                }
        }
    phrase = newPass;

    int test1[pass.length()];
    for( int x = 0; x < phrase.length(); x++ )
        {
            test1[x] = 0;
            if( pass[x] != ' ' )
                {
                    for( int y = 0; y < alphabet.length(); y++ )
                        {
                            if( phrase[x] == alphabet[y] )
                                {
                                    test1[x] += y;
                                }
                            if( pass[x] == alphabet[y] )
                                {
                                    test1[x] += y;
                                }
                        }
                }
            else
                {
                    test1[x] = 99999;
                }
        }
    for( int i = 0 ; i < sizeof( test1 ) / sizeof( test1[0] ); i++ )
        {
            if( test1[i] != 99999 )
                {
                    while( test1[i] > 25 )
                        {
                            test1[i] -= 26;
                        }
                }
        }
    for( int i = 0 ; i < sizeof( test1 ) / sizeof( test1[0] ); i++ )
        {
            if( test1[i] == 99999 )
                {
                    decy += ' ';
                }
            else
                {
                    for( int y = 0; y < alphabet.length(); y++ )
                        {
                            if( test1[i] == y )
                                {
                                    decy += alphabet[y];
                                }
                        }
                }
        }

    cout << "\nThe encrypted message : " << decy << endl;
    return 0;
}
int decrypt()
{
    string alphabet = "abcdefghijklmnopqrstuvwxyz";

    char text1[300];
    string decy = "";
    cout << "Enter message to decrypt: ";
    cin.getline ( text1, 300 );
    decy = text1;

    char text2[300];
    string phrase = "";
    cout << "Enter key: ";
    cin.getline ( text2, 300 );
    phrase = text2;

    string pass = "";
    string newPass = "";

    for( int a = 0, r = 0; newPass.length() < decy.length(); r++ )
        {
            if( decy[r] == ' ' )
                {
                    newPass += ' ';
                }
            else
                {
                    newPass += phrase[a];
                    a++;
                }
            if( a >= phrase.length() )
                {
                    a = 0;
                }
        }
    phrase = newPass;
    int test1[decy.length()];
    for( int x = 0; x < phrase.length(); x++ )
        {
            if( decy[x] != ' ' )
                {
                    int fr = 0;
                    int to = 0;
                    for( int y = 0; y < alphabet.length(); y++ )
                        {
                            if( phrase[x] == alphabet[y] )
                                {
                                    fr = y;
                                }
                            if( decy[x] == alphabet[y] )
                                {
                                    to = y;
                                }
                        }
                    test1[x] = to - fr;
                    while( test1[x] < 0 )
                        {
                            test1[x] += 26;
                        }
                }
            else
                {
                    test1[x] = 99999;
                }
        }

    for( int i = 0 ; i < sizeof( test1 ) / sizeof( test1[0] ); i++ )
        {
            if( decy[i] != ' ' )
                {
                    for( int y = 0; y < alphabet.length(); y++ )
                        {
                            if( test1[i] == y )
                                {
                                    pass += alphabet[y];
                                }
                        }
                }
            else
                {
                    pass += ' ';
                }
        }

    cout << "\nThe decrypted message is: " << pass << endl;
    return 0;
}
int main()
{
    bool ok = true;
    while( ok )
        {
            string chose = "";
            cout << "[e] . Encipher" << endl;
            cout << "[d] . Decipher" << endl;
            cout << "[x] . Exit \n " << endl;
            cout << "Enter Choice: ";
            cin >> chose;
            cin.ignore();
            if( chose == "e" )
                {

                    encrypt();
                    char menu;

                    cout << "\nBack to main menu? (y/n): ";
                    cin >> menu;

                    if ( menu == 'n' )
                        {
                            ok = false;
                        }
                }
            else if( chose == "d" )
                {
                    decrypt();
                    char menu;

                    cout << "\nBack to main menu? (y/n): ";
                    cin >> menu;

                    if ( menu == 'n' )
                        {
                            ok = false;
                        }
                }
            else if( chose == "x" )
                {
                    ok = false;
                }
            else
                {
                    cout << "---";
                }



        }

    return 0;

}
