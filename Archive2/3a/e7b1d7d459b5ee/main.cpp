touch {A..Z}

ls ? | for a in Folder\ {1..8}; do mkdir -pv "$a"; read z && read y && read x && read w; mv -v "$z" "$y" "$x" "$w" "$a/"; done

echo ======================
find 
