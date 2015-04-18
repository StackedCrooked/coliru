#include <iostream>
#include <complex>

#include <vector>

#include <thread>
#include <Windows.h>
using namespace std;

int main()
{
   const int M = 150;
   const int N = 150;
   const int K = 150;

   vector<complex<float>> v1(M*N);
   vector<complex<float>> v2(N*K);
   vector<complex<float>> v3(M*K);

   for (int k = 0; k < M*N; ++k)
   {
      v1[k] = complex<float>(float(k), float(k));
   }

   for (int k = 0; k < N*K; ++k)
   {
      v2[k] = complex<float>(float(k), float(k));
   }

   LARGE_INTEGER frequency, start_time, end_time;

   QueryPerformanceFrequency(&frequency);
   QueryPerformanceCounter(&start_time);
   for (int i = 0; i < M; ++i)
   {
      for (int k = 0; k < K; ++k)
      {
         complex<float> sum(0.0f, 0.0f);
         for (int j = 0; j < N; ++j)
         {
            int idx1 = i*N + j;
            int idx2 = k*N + j;
            sum += v1[idx1] * v2[idx2];
            //float re = v1[idx1].real() * v2[idx2].real() -
            //   v1[idx1].imag()*v2[idx2].imag();
            //float im = v1[idx1].real()*v2[idx2].imag() +
            //   v1[idx1].imag()*v2[idx2].real();
            //sum.real(sum.real() + re);
            //sum.imag(sum.imag() + im);
         }
         v3[i*K + k] = sum;
      }
   }
   QueryPerformanceCounter(&end_time);
   LARGE_INTEGER elapsed_us;
   elapsed_us.QuadPart = (end_time.QuadPart - start_time.QuadPart) * 1000000 / frequency.QuadPart;
   cout << "Total time in microseconds = " << elapsed_us.QuadPart << endl;
   this_thread::sleep_for(chrono::seconds(5));
}