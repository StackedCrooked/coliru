#!/bin/bash -x

git init .
git fast-import

git log --graph --all --decorate --left-right