cat > expressions.xml <<XML; g++ -std=c++11 -Os -pedantic main.cpp && ./a.out
<expressions>
  <addition id="1">
    <item>2</item>
    <item>3</item>
    <item>4</item>
  </addition>
  <subtraction id="2">
    <minuend>3</minuend>
    <subtrahend>2</subtrahend>
  </subtraction>
  <multiplication id="3">
    <factor>5</factor>
    <factor>6</factor>
    <factor>8</factor>
  </multiplication>
  <division id="4">
    <dividend>54</dividend>
    <divisor>9</divisor>
  </division>
</expressions>
XML