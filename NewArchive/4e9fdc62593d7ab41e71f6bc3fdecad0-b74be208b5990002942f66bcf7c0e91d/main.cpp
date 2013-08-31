cd /Archive
ls | base64 | cut -c -10 | sort | uniq | wc -l
ls | base64 | wc -l
