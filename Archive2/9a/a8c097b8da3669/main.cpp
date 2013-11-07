#include <iostream>
#include <string>
#include <vector>
#include <memory>

using std::cout;
using std::endl;

int main()
{
 
    int N, K;
 
    N = 5;
    K = 3;
    
    float somme = 0;
 
    /*do{
        cin >> N;
        cin >> K;
    }while( N <= 0 && K <= 0 && N < K);
 */
    std::unique_ptr<int[]> t { new int[N] };
   // float t[N];
 
    for( int i = 0; i < N; i++)
    {
        t[i] = i+1;//rand()%10;
        //cin >> t[i];
        cout << t[i];
        if ( i != N - 1 ) cout << ", ";
    }
    cout << endl;
 
    for( int i = 0; i < K; i++)
    {
        somme += t[i];
    }
 
    for( int j = 1; j < N - K + 1; j++) // manquait un +1 ici pour le dernier range à tester
    {
        int a = 0;
 
        for( int i = 0; i < K; i++)
        {
            a += t[i+j];
        }
        if( a > somme) somme = a;
    }
 
    cout << somme;
 
    return 0;
}
