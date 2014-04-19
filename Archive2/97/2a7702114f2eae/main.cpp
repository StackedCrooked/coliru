Named functions
---------------------------

fun f (p1 : t1, p2 : t2, ..., pn : tn) -> rt := body

# f's type is "(t1, t2, ..., tn) -> rt"

# "-> rt" can be omitted . the type is then inferred from the return
# expression(s)

The parenthesis can be omitted if there are no parameters:

fun f -> int := 10



Calling functions
---------------------

f (a1, a2, ..., an)



Unnamed functions
-------------------------------

fun (p1 : t1, p2 : t2, ..., pn : tn) -> rt := ...

For disambiguation, the construct can be enclosed in parenthesis. Nullary function with omitted
return type passed to a function:

fun f (p1 : -> bool) := p1 () # define f
f (fun := true) # call f



Variables
-----------------

var i : type := value

# i's type is "type"



Expressions
---------------

- Integer and float literals as usual
- Text string literals are in utf8: "hello"

Floats are 64bit double precision IEEE754 floating points. Ints are 64bit signed integers

Operators
----------------

+, -, *, /, % as usual. No conversions take place at all.


Equality/relational operators: =, !=, <=, >=, <, >



Statements
----------------

All statements evaluate to a value



Assignment
---------------

e := v

An assignment evaluates to the value of "e", after it has been assigned. Assignments can only appear as a toplevel
element of a statement sequence (but the statement sequence may itself be a substatement)



Blocks
----------------

{ cmd1, cmd2, ..., cmdn }

The value of a block is the value of its right-most element.



Loops
------------------

while (cmd0) cmd1

A while loop evaluates to the value "none"


for (init-cmd; while-cmd; step-cmd) cmd

A for loop evaluates to "none"



Conditional jumps
---------------------

if (cmd0) cmd1 else cmd2

An "if" statement evaluates to either "cmd1" or "cmd2", depending on what statement was evaluated.

