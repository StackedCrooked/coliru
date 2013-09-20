set -x ; g++-4.8 -std=c++11 -O2 -Wall -pedantic main.cpp && ./a.out <<GIT_REPO
blob
mark :1
data 178
twas a bright sunny day
when sheep were frollicking
and the whollop chimed in
golden brounding

the treetops ruffled Jimmy's
feathers 
as riddled twiddly-diddly
fiddles giddied


reset refs/heads/master
commit refs/heads/master
mark :2
author Seth Heeren <sgheeren@gmail.com> 1379453041 +0200
committer Seth Heeren <sgheeren@gmail.com> 1379453041 +0200
data 2
a
M 100644 :1 a

blob
mark :3
data 242
twas a bright sunny day
when sheep were frollicking
and the whollop chimed in
golden brounding

the treetops ruffled Jimmy's
feathers 
as riddled twiddly-diddly
fiddles giddied

no problems arose
when adding prose
at the end,
however verbose

commit refs/heads/diverge
mark :4
author Seth Heeren <sgheeren@gmail.com> 1379453112 +0200
committer Seth Heeren <sgheeren@gmail.com> 1379453112 +0200
data 13
added stanza
from :2
M 100644 :3 a

blob
mark :5
data 181
twas a bright sunny day
when sheep were frollicking
and the whollop chimed in
golden tjullockings

the treetops ruffled Jimmy's
feathers 
as riddled twiddly-diddly
fiddles giddied


commit refs/heads/master
mark :6
author Seth Heeren <sgheeren@gmail.com> 1379453148 +0200
committer Seth Heeren <sgheeren@gmail.com> 1379453148 +0200
data 21
tjullocking favoured
from :2
M 100644 :5 a

blob
mark :7
data 278
twas a bright sunny day
when sheep were frollicking
and the whollop chimed in
golden tjullockings

the treetops ruffled Jimmy's
feathers 
as riddled twiddly-diddly
fiddles giddied

the end is near
with fierce and dark
encompass
tis what you fear that clears
the mind and throat

commit refs/heads/master
mark :8
author Seth Heeren <sgheeren@gmail.com> 1379453205 +0200
committer Seth Heeren <sgheeren@gmail.com> 1379453205 +0200
data 23
ludicrous extra stanza
from :6
M 100644 :7 a

blob
mark :9
data 282
't was a bright sunny day
when sheep were frollicking
and the whollop chimed 
in golden tjullockings

the tree-tops rustled Jimmy's
feathers 
as riddled twiddly-diddly
fiddles giddied

the end is near
with fierce and dark
encompass
tis what you fear that clears
the mind and throat

commit refs/heads/master
mark :10
author Seth Heeren <sgheeren@gmail.com> 1379453246 +0200
committer Seth Heeren <sgheeren@gmail.com> 1379453246 +0200
data 11
editorials
from :8
M 100644 :9 a

GIT_REPO