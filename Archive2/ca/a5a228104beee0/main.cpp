#!/bin/bash
set -x -e
git init .

# create 26 commits
for a in {a..z}; do touch $a && git add $a && git commit -m "added $a"; done

# tag (commit 'p') one as our previous RELEASE_A
git tag RELEASE_A HEAD~10

# now we do a release without patches h, t, p, and w:
culprits=$(git rev-list --grep='[htpw]' RELEASE_A..HEAD)
git revert --no-edit $culprits
git tag RELEASE_B

# re-apply the culprits:
git cherry-pick $culprits

# end result:
git log --decorate --oneline