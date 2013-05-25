template<typename T>
void pipes(const int pipeN) {
    hdnum::DenseMatrix<T> pointPressure(pipeN*pipeN, pipeN*pipeN, 0);
	//pointPressure.iwidth(2);
	pointPressure.width(2);
	//pointPressure.precision(0);
	--pointPressure[0][1];//upleft+right
	--pointPressure[0][pipeN];//upleft+down
	--pointPressure[pipeN-1][pipeN-1 -1];//upright+left
	--pointPressure[pipeN-1][pipeN-1 +pipeN];//upright+down
	--pointPressure[pipeN*pipeN-pipeN][pipeN*pipeN-pipeN -pipeN];//downleft+up
	--pointPressure[pipeN*pipeN-pipeN][pipeN*pipeN-pipeN +1];//downleft+right
	--pointPressure[pipeN*pipeN-pipeN+pipeN-1][pipeN*pipeN-pipeN+pipeN-1 -1];//downright+left
	--pointPressure[pipeN*pipeN-pipeN+pipeN-1][pipeN*pipeN-pipeN+pipeN-1 -pipeN];//downright+up
	for(int vertexIndex = 1; vertexIndex < pipeN -1; ++vertexIndex) {//first row
		--pointPressure[vertexIndex][vertexIndex -1];//left
		--pointPressure[vertexIndex][vertexIndex +pipeN];//down
		--pointPressure[vertexIndex][vertexIndex +1];//right
	}
	for(int vertexIndex = pipeN*pipeN-pipeN+1; vertexIndex < pipeN*pipeN-pipeN+pipeN -1; ++vertexIndex) {//last row
		--pointPressure[vertexIndex][vertexIndex -1];//left
		--pointPressure[vertexIndex][vertexIndex -pipeN];//up
		--pointPressure[vertexIndex][vertexIndex +1];//right
	}
	for(int pipeRow = 1; pipeRow < pipeN -1; ++pipeRow) {
		int vertexIndex = pipeRow*pipeN;
		--pointPressure[vertexIndex][vertexIndex -pipeN];//up
		--pointPressure[vertexIndex][vertexIndex +1];//right
		--pointPressure[vertexIndex][vertexIndex +pipeN];//down
		for(++vertexIndex; vertexIndex < pipeRow*pipeN+pipeN-1; ++vertexIndex) {
			--pointPressure[vertexIndex][vertexIndex -1];//left
			--pointPressure[vertexIndex][vertexIndex -pipeN];//up
			--pointPressure[vertexIndex][vertexIndex +1];//right
			--pointPressure[vertexIndex][vertexIndex +pipeN];//down
		}
		--pointPressure[vertexIndex][vertexIndex -1];//left
		--pointPressure[vertexIndex][vertexIndex -pipeN];//up
		--pointPressure[vertexIndex][vertexIndex +pipeN];//down
	}
	for(int row = 0; row < pipeN*pipeN; ++row)
	for(int column = 0; column < pipeN*pipeN; ++column)
		if(row!=column) pointPressure[row][row] -= pointPressure[row][column];

	std::cout << pointPressure << std::endl;
}