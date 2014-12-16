#include <string>
#include <sstream>
#include <cassert>
#include <chrono>
#include <iostream>
#include <cstdio>
using namespace std;
using namespace std::chrono;

string float_to_string(float f)
{
   stringstream sstr;
   sstr << f;
   return sstr.str();
}

float string_to_float(string s)
{
   stringstream sstr{ s };
   float f;
   sstr >> f;
   return f;
}

string float_to_string_C(float f)
{
   char buf[64] = { 0 };
   sprintf(buf, "%f", f);
   return string(buf);
}

float string_to_float_C(string s)
{
   char buf[64] = { 0 };
   copy(begin(s), end(s), buf + 0);
   float f;
   sscanf(buf, "%f", &f);
   return f;
}

string float_to_string(float f, stringstream &sstr)
{
   sstr.str("");
   sstr.clear();
   sstr << f;
   return sstr.str();
}

float string_to_float(string s, stringstream &sstr)
{
   sstr.str("");
   sstr.clear();
   sstr << s;
   float f;
   sstr >> f;
   return f;
}

float convert_back_forth(float f)
{
   return string_to_float(float_to_string(f));
}

float convert_back_forth(float f, stringstream &sstr)
{
   return string_to_float(float_to_string(f, sstr), sstr);
}

float convert_back_forth_C(float f)
{
   return string_to_float_C(float_to_string_C(f));
}



int main()
{
   enum { N = 1000000 };
   //
   // With stringstream, using a local stream
   //
   {
      float f = 1.f;
      auto before = system_clock::now();
      for (int i = 0; i < N; ++i)
         f = convert_back_forth(f);
      auto after = system_clock::now();
      cout << "With stringstream, using a local stream: "
         << duration_cast<milliseconds>(after - before).count()
         << " ms\n(dummy result: " << f << ")\n";
   }
   //
   // With stringstream, using a recycled stream
   //
   {
      float f = 1.f;
      auto before = system_clock::now();
      stringstream sstr;
      for (int i = 0; i < N; ++i)
         f = convert_back_forth(f, sstr);
      auto after = system_clock::now();
      cout << "With stringstream, using a recycled stream: "
         << duration_cast<milliseconds>(after - before).count()
         << " ms\n(dummy result: " << f << ")\n";
   }
   //
   // With C-style functions from <cstdio>
   //
   {
      float f = 1.f;
      auto before = system_clock::now();
      for (int i = 0; i < N; ++i)
         f = convert_back_forth_C(f);
      auto after = system_clock::now();
      cout << "With C-style I/O: "
         << duration_cast<milliseconds>(after - before).count()
         << " ms\n(dummy result: " << f << ")\n";
   }
}