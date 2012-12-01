#!/bin/bash
TAB="$(printf '\t')"
echo "$(printf %q $(cat $1))${TAB}$(printf %q $(cat $2))"
