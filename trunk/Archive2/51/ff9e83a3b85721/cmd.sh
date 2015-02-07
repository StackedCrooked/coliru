cat>input.txt<<XML; g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out 
<node id="A.html">
    <subnode> child A1 </subnode>
    <subnode> child A2 </subnode>
</node>

<node id="B.html">
    <subnode> child B1 </subnode>
    <subnode> child B2 </subnode>
</node>
XML