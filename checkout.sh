#!/bin/bash
mkdir coliru
cd coliru
for i in $(echo Web Installer Todo.txt) ; do
    svn co https://coliru.googlecode.com/svn/trunk/${i} ${i}
done

echo "Checking out the Archive in the background."
svn co https://coliru.googlecode.com/svn/trunk/Archive Archive >/dev/null 2>&1 & disown
