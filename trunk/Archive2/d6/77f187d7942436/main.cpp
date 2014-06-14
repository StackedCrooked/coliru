
# prepare files
for a in file{1..116}.html; do echo '<script>var ppgnum =0;</script>' > "$a"; done

# replace
for filename in file*.html; do       sed -i "s/var ppgnum =0;/var ppgnum =${filename//[^0-9]/};/" "$filename"; done

# print
grep . file*.html