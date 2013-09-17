#!/bin/bash
set -x -e
git init .

git config user.name 'demo'
git config user.email 'demo.example.com'

echo "##############################################"
echo "# create 26 commits"
for a in a b c d e f g h i j k l m n o p q r s t u v w x y z
do 
    touch $a && git add $a && git commit -m "added $a"
done

echo "tag (commit 'p') one as our previous RELEASE_A"
git tag RELEASE_A HEAD~10

echo "##############################################"
echo "# now we do a release without patches h, t, p, and w:"
culprits=$(git rev-list --grep='[htpw]' RELEASE_A..HEAD)
git revert --no-edit $culprits
git tag RELEASE_B

echo "# re-apply the culprits:"
git cherry-pick $culprits

echo "##############################################"
echo "# end result:"
git log --decorate --oneline