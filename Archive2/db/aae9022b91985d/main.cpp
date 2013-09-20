#!/bin/bash -x

git init .
git config user.name 'sehe'
git config user.email 'sehe@example.com'
git fast-import 2>&1 > /dev/null

git show-branch

git log --graph --all --decorate --left-right

git checkout -b be_merged
git merge diverge
git reset
echo "brute force resolution (because I have no monkeys in the cloud)" > a

git commit -m 'merge boundary commit'
git commit -am 'and the resolutions'

git log -2 -p