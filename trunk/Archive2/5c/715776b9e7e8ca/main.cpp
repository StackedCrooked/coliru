(base64 -d | xzcat | cpio -i) <<DEMO_FILES
/Td6WFoAAATm1rRGAgAhARwAAAAQz1jM4BX/AcldAGOcPkABcxwX47F5En1gbluGIVhed675PoKEkEI3W1/uGFKyhacF5+SxoPLppUl+O+149LNaoCctX9ILt3XjTyEPvN+kvcoFqLS3
XfUsVl2LDzl8dSSd8YtXTzTz2Snfl/ai1E6memtDXpSOI08OSoZzk2giox/sCsgH6mwE3pngx62m1X20ZFcbQBP5/0u+G7Bcr+5aRtNeXiAZwy3OBbTQxNyW6KGKZohtEQPqXI5NtYuf
oFIW+tcDIPVlcwdR5xFyzf4zECFqyRZEm2LH5EVGr5DQl7+UKlaauNDwk+aFU+vIYXrgXYpV5IegKeCnbAShSRPDS4QqkfT+VmXzGojAAbrpjwbcMc7ixAJ7LF98LQuZbIob8s5OpUpk
eoib+5EWArzE7EAKImGCq/HdV7u5XSdyZMUbZF514RF2zlb9JUujCgg7a9ZTOGMAiYZPr9kaWnytRQzc+R2KLZsGodtKuRDnfL4CvBXGwLhy+8Aokq/a1sZZRgA9MeBXKmJTj7hTC7Xk
N2yioAbnfhMs9iQhU0GNcZco1wNopbpOtAF8z8BMyVT3ELmRi2rMEPg9xHrC9kjtgfv3hhJJPQNTzqdOA3BDplg8c8QAAAAAzSTTGE5GxgMAAeUDgCwAAIMtch6xxGf7AgAAAAAEWVo=
DEMO_FILES

for a in */*/*.csv
do 
    dname="$(basename "$(dirname "$a")")"
    echo -e "$dname\t$(sort -t"," -k3,3g "$a" | tail -n 1)"
done