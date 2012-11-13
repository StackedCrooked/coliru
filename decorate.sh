ID=`md5sum main.cpp | cut -d ' ' -f 1`
DIR="Archive/${ID}"
mkdir -p ${DIR}
cp main.cpp "${DIR}/main.cpp"
#./compile.sh && ./main.o > "${DIR}/output.txt" 2>&1 && cat ${DIR}/output.txt && echo "URL: " && echo "_URL_${DIR}/output.txt"
./compile.sh > "${DIR}/output.txt" 2>&1 && ./main.o >> "${DIR}/output.txt"
echo ${ID}
