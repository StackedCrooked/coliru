touch {A..Z}

for a in Folder\ {1..8}; do mkdir -p "$a"; read z && read y && read x && read w; mv "$z" "$y" "$x" "$w" "$a/"; done < <(ls ?)

echo ======================
find 
