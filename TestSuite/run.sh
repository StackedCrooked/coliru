set -x
for dir in `ls` ; do cd $dir && cat main.cpp && ../../Web/sandbox.sh ; cd - ; done
