ID=`./checksum.sh main.cpp | cut -d ' ' -f 1`
DIR="Archive/${ID}"
if [ ! -d ${DIR} ] ; then
	mkdir -p ${DIR}
	cp main.cpp "${DIR}/main.cpp"
	./compile.sh > "${DIR}/output.txt" 2>&1 && ./main.o >> "${DIR}/output.txt"
fi
echo ${ID}
