clang++ -std=c++11 -Os -Wall -pedantic main.cpp && cat >input.txt <<INPUT && ./a.out
Test_Q := LE600ms.Signal12;
Test_A := Signal1;
Test_Z := (Signal1);
Test_B := (Signal1 OR Signal12) AND Signal3;
Test_A.expire := Signal2;

Output_B :=
    LE600ms.{
    (LE1s.{FE1s.{Signal1}} AND
    LE1s.{FE1s.{Signal2}})
    OR
    (LE3ms.{FE2ms.{NOT.Signal3}} AND
    LE3ms.{FE2ms.{Signal4}})};
INPUT