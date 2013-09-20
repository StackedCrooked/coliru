#!/bin/bash -x

git init .
git config user.name='sehe'
git config user.email='sehe@example.com'
git fast-import

git log --graph --all --decorate --left-right