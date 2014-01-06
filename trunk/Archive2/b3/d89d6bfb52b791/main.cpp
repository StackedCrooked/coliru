preprocessing-ﬁle:
groupopt
group:
group-part
group group-part
group-part:
if-section
control-line
text-line
# non-directive
if-section:
if-group elif-groupsopt else-groupopt endif-line
if-group:
# if constant-expression new-line groupopt
# ifdef identiﬁer new-line groupopt
# ifndef identiﬁer new-line groupopt
elif-groups:
elif-group
elif-groups elif-group
elif-group:
# elif constant-expression new-line groupopt
else-group:
# else new-line groupopt
endif-line:
# endif new-line
control-line:
# include pp-tokens new-line
# define identiﬁer replacement-list new-line
# define identiﬁer lparen identiﬁer-listopt) replacement-list new-line
# define identiﬁer lparen ... ) replacement-list new-line
# define identiﬁer lparen identiﬁer-list, ... ) replacement-list new-line
# undef identiﬁer new-line
# line pp-tokens new-line
# error pp-tokensopt new-line
# pragma pp-tokensopt new-line
# new-line
text-line:
pp-tokensopt new-line
non-directive:
pp-tokens new-line
lparen:
a ( character not immediately preceded by white-space
identiﬁer-list:
identiﬁer
identiﬁer-list , identiﬁer
replacement-list:
pp-tokensopt
pp-tokens:
preprocessing-token
pp-tokens preprocessing-token
new-line:
the new-line character