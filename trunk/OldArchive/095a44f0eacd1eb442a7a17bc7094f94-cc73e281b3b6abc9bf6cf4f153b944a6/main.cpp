the input does not match the var type OR x is anything other than 1, 2, or 3. 
(the input does not match the var type) OR (x is anything other than 1, 2, or 3.)
(cin.fail()) OR (x is not one AND x is not two AND x is not three)
(cin.fail()) OR ((x is not one) AND (x is not two) AND (x is not three))
(cin.fail()) OR ((x!=1) AND (x!=2) AND (x!=3))
(cin.fail()) || ((x!=1) && (x!=2) && (x!=3))
=== Now, a tricky bit:  `((A)&&(B)) is the same as `(!A)||(!B)`
(cin.fail()) || (x==1) || (x==2) || (x==3))
stop when input was bad, or if x is one, two, or three. 