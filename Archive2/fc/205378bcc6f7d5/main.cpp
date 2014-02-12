#include <iostream>
#include <chrono>
#include <ctime>
 
long fibonacci(int n)
{
    if (n < 3) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}
 int q_round1 ( int Q )
 {
    if (0 == Q)
        return 1;

    int result = 0;
    for (int i=-Q; i<=Q; ++i) {
        for(int j=-Q; j<=Q; ++j) {
            if (Q == (i*i + j*j)) {
                ++result;
                                  }
        }
    }
    return result;
}

int q_round2 ( int Q ) {
    if (0 == Q)
        return 1;

    int result = 0;
    for (int i=0; i<=Q; ++i) {
        for(int j=i; j<=Q; ++j) {
            if (Q == (i*i + j*j)) {
                if (i != j) {
                    if (0 < i && 0 < j)
                        // [ (i,j), (-i,j), (i,-j), (-i,-j), (j,i), (-j,i), (j,-i), (-j,-i) ]
                        result+=8;
                    else
                        // [ (0,j), (0,-j), (j,0), (-j,0) ] || [ (i,0), (-i,0), (0,i), (0,-i) ]
                        result+=4;
                } else {
                    // [ (i,i), (-i,i), (i,-i), (-i,-i) ]
                    result+=4;
                }
            }
        }
    }
    return result;
}

int q_round3 ( int Q ) {
    if (0 == Q)
        return 1;

    int result = 0;
    for (int i=0, i2=0; i2<=Q; ++i, i2=i*i) {
        for(int j=i, j2=j*j; j2<=(Q-i2); ++j, j2=j*j) {
            if (Q == (i2 + j2)) {
                if (i != j) {
                    if (0 < i && 0 < j)
                        // [ (i,j), (-i,j), (i,-j), (-i,-j), (j,i), (-j,i), (j,-i), (-j,-i) ]
                        result+=8;
                    else
                        // [ (0,j), (0,-j), (j,0), (-j,0) ] || [ (i,0), (-i,0), (0,i), (0,-i) ]
                        result+=4;
                } else {
                    // [ (i,i), (-i,i), (i,-i), (-i,-i) ]
                    result+=4;
                }
            }
        }
    }
    return result;
}
int main()
{
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for(int i=0; i<150; ++i) {
        int q1 = q_round1(i);
        cout << "q_round1(" << setw(4) << i << ") = " << setw(4) << q1 << " ";

        int q2 = q_round2(i);
        cout << "q_round2(" << setw(4) << i << ") = " << setw(4) << q2 << " ";

        int q3 = q_round3(i);
        cout << "q_round3(" << setw(4) << i << ") = " << setw(4) << q3 << endl;
    end = std::chrono::system_clock::now();
 
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
 
    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";
}