cd /Archive
ls | cut -c -10 | base64 | sort | uniq | wc -l
ls | base64 | wc -l
