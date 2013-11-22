#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstring>

#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

#include <immintrin.h>

#include "aligned_allocator.h"

template<typename matrix_t>
matrix_t matrixMul(const matrix_t & matrixA, const matrix_t & matrixB) {
    const auto dimension = matrixA.size();

	assert(matrixA.size() == dimension);
	assert(matrixA[0].size() == dimension);
	assert(matrixB.size() == dimension);
	assert(matrixB[0].size() == dimension);

	matrix_t matrixC(dimension, typename matrix_t::value_type(dimension, 0));//0ed matrix

	for(size_t x{0}; x < dimension; ++x)
	for(size_t i{0}; i < dimension; ++i)
	for(size_t y{0}; y < dimension; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	return matrixC;//move semantics ftw
}

template<typename matrix_t>
matrix_t matrixMulFMA(const matrix_t & matrixA, const matrix_t & matrixB) {
	const auto dimension = matrixA.size();

	assert(matrixA.size() == dimension);
	assert(matrixA[0].size() == dimension);
	assert(matrixB.size() == dimension);
	assert(matrixB[0].size() == dimension);

	matrix_t matrixC(dimension, typename matrix_t::value_type(dimension, 0));//0ed matrix

	const size_t vec = 8;
	const size_t start{dimension - dimension % vec};

	if(dimension > vec) {
		for(size_t x{0}; x < dimension; ++x)
		for(size_t i{0}; i < dimension; ++i) {
			const __m256 a = _mm256_set_ps(matrixA[x][i], matrixA[x][i], matrixA[x][i], matrixA[x][i], matrixA[x][i], matrixA[x][i], matrixA[x][i], matrixA[x][i]);// unaligned read
			for(size_t y{0}; y < start; y += vec) {
				//__m256 c = _mm256_set_ps(matrixC[x][y+7], matrixC[x][y+6], matrixC[x][y+5], matrixC[x][y+4], matrixC[x][y+3], matrixC[x][y+2], matrixC[x][y+1], matrixC[x][y+0]);
				//const __m256 b = _mm256_set_ps(matrixB[i][y+7], matrixB[i][y+6], matrixB[i][y+5], matrixB[i][y+4], matrixB[i][y+3], matrixB[i][y+2], matrixB[i][y+1], matrixB[i][y+0]);

				__m256 c = *reinterpret_cast<__m256*>(&matrixC[x][y]);// aligned read
				const __m256 & b = *reinterpret_cast<const __m256*>(&matrixB[i][y]);// aligned read

				c = _mm256_fmadd_ps(a, b, c);//c = a * b + c;

				//_mm256_store_ps(&matrixC[x][y], c);//aligned
				//_mm256_storeu_ps(&matrixC[x][y], c);//unaligned

				/*
				float c[8];
				c[0] = matrixC[i][y+0];
				c[1] = matrixC[i][y+1];
				c[2] = matrixC[i][y+2];
				c[3] = matrixC[i][y+3];
				c[4] = matrixC[i][y+4];
				c[5] = matrixC[i][y+5];
				c[6] = matrixC[i][y+6];
				c[7] = matrixC[i][y+7];

				c[0] += matrixA[x][i] * matrixB[i][y+0];
				c[1] += matrixA[x][i] * matrixB[i][y+1];
				c[2] += matrixA[x][i] * matrixB[i][y+2];
				c[3] += matrixA[x][i] * matrixB[i][y+3];
				c[4] += matrixA[x][i] * matrixB[i][y+4];
				c[5] += matrixA[x][i] * matrixB[i][y+5];
				c[6] += matrixA[x][i] * matrixB[i][y+6];
				c[7] += matrixA[x][i] * matrixB[i][y+7];
				//*/
				//*
				matrixC[x][y+0] = c[0];
				matrixC[x][y+1] = c[1];
				matrixC[x][y+2] = c[2];
				matrixC[x][y+3] = c[3];
				matrixC[x][y+4] = c[4];
				matrixC[x][y+5] = c[5];
				matrixC[x][y+6] = c[6];
				matrixC[x][y+7] = c[7];
				//*/

				/*is doing this
				matrixC[x][y+0] += matrixA[x][i] * matrixB[i][y+0];
				matrixC[x][y+1] += matrixA[x][i] * matrixB[i][y+1];
				matrixC[x][y+2] += matrixA[x][i] * matrixB[i][y+2];
				matrixC[x][y+3] += matrixA[x][i] * matrixB[i][y+3];
				matrixC[x][y+4] += matrixA[x][i] * matrixB[i][y+4];
				matrixC[x][y+5] += matrixA[x][i] * matrixB[i][y+5];
				matrixC[x][y+6] += matrixA[x][i] * matrixB[i][y+6];
				matrixC[x][y+7] += matrixA[x][i] * matrixB[i][y+7];
				//*/
			}
		}
	}

	//calculate remaining columns
	for(size_t x{0}; x < dimension; ++x)
	for(size_t i{0}; i < dimension; ++i)
	for(size_t y{start}; y < dimension; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	return matrixC;//move semantics ftw
}

template<typename matrix_t>
matrix_t matrixMulRotated(const matrix_t & matrixA, const matrix_t & matrixB) {
	const auto dimension = matrixA.size();

	assert(matrixA.size() == dimension);
	assert(matrixA[0].size() == dimension);
	assert(matrixB.size() == dimension);
	assert(matrixB[0].size() == dimension);

	auto matrixBT = matrixB;

	for(size_t x{0}; x < dimension; ++x)
	for(size_t y{0}; y < dimension; ++y)
		matrixBT[x][y] = matrixB[y][x];

	matrix_t matrixC(dimension, typename matrix_t::value_type(dimension, 0));//0ed matrix

	for(size_t x{0}; x < dimension; ++x)
	for(size_t y{0}; y < dimension; ++y)
	for(size_t i{0}; i < dimension; ++i)
		matrixC[x][y] += matrixA[x][i] * matrixBT[y][i];

	return matrixC;//move semantics ftw
}

template<typename matrix_t>
matrix_t matrixMulTiled(const matrix_t & matrixA, const matrix_t & matrixB) {
	const auto dimension = matrixA.size();

	assert(matrixA.size() == dimension);
	assert(matrixA[0].size() == dimension);
	assert(matrixB.size() == dimension);
	assert(matrixB[0].size() == dimension);

	matrix_t matrixC(dimension, typename matrix_t::value_type(dimension, 0));//0ed matrix

	const int m{8};//256bit
	const size_t n{dimension - dimension % m};

	if(n >= m) {
		for (size_t i{0}; i < n; i+=m)
		for (size_t j{0}; j < n; j+=m)
		for (size_t k{0}; k < n; k+=m)
		for (size_t s{0}; s < m; s++)
		for (size_t t{0}; t < m; t++)
		for (size_t u{0}; u < m; u++)
			matrixC[i + s][j + t] += matrixA[i + s][k + u] * matrixB[k + u][j + t];
	}

	//finalize calculations within tiles
	for(size_t x{0}; x < n; ++x)
	for(size_t i{n}; i < dimension; ++i)
	for(size_t y{0}; y < n; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	//calculate remaining rows
	for(size_t x{n}; x < dimension; ++x)
	for(size_t i{0}; i < dimension; ++i)
	for(size_t y{0}; y < dimension; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	//calculate remaining elements (remaining columns without already calculated rows)
	for(size_t x{0}; x < n; ++x)
	for(size_t i{0}; i < dimension; ++i)
	for(size_t y{n}; y < dimension; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	return matrixC;//move semantics ftw
}

template<typename matrix_t>
matrix_t matrixMulUnrolled(const matrix_t & matrixA, const matrix_t & matrixB) {
	const auto dimension = matrixA.size();

	assert(matrixA.size() == dimension);
	assert(matrixA[0].size() == dimension);
	assert(matrixB.size() == dimension);
	assert(matrixB[0].size() == dimension);

	matrix_t matrixC(dimension, typename matrix_t::value_type(dimension, 0));//0ed matrix

	const size_t vec{4};
	const size_t start{dimension - dimension % vec};

	if(dimension > vec) {
		for(size_t x{0}; x < dimension; ++x)
		//for(size_t i{0}; i < dimension; ++i)
		for(size_t i{0}; i < start; i += vec)
		for(size_t y{0}; y < dimension; ++y)
		//for(size_t y{0}; y < dimension - vec; y += vec)
		for(size_t t{0}; t < vec; ++t)
			matrixC[x][y] += matrixA[x][i+t] * matrixB[i+t][y];
			//matrixC[x][y+t] += matrixA[x][i] * matrixB[i][y+t];
	}

	for(size_t x{0}; x < dimension; ++x)
	//for(size_t i{0}; i < dimension; ++i)
	for(size_t i{start}; i < dimension; ++i)
	for(size_t y{0}; y < dimension; ++y)
	//for(size_t y{start}; y < dimension; ++y)
		matrixC[x][y] += matrixA[x][i] * matrixB[i][y];

	return matrixC;//move semantics ftw
}

template<typename matrix_t>
matrix_t gaussSeidelIteration(const matrix_t & grid) {
	const auto dimension = grid.size();

	assert(grid[0].size() == dimension);

	auto gridCopy = grid;

	for(size_t x{1}; x < dimension - 1; ++x)
	for(size_t y{1}; y < dimension - 1; ++y)
		gridCopy[x][y] = 0.25f * (grid[x-1][y] + grid[x][y-1] + grid[x][y+1] + grid[x+1][y]);

	return gridCopy;
}

template<typename matrix_t, typename T>
bool testMatrixMul(T function) {
	matrix_t matrix = {//first 100 mt19937 digits
		{5,5,7,8,6,8,5,8,4,6},
		{6,3,4,2,8,0,9,2,3,4},
		{7,8,5,4,5,3,9,8,0,3},
		{0,6,0,3,8,9,7,1,8,8},
		{9,4,7,8,4,5,7,6,1,7},
		{6,5,1,5,9,7,5,1,4,4},
		{2,1,7,7,4,2,5,1,0,3},
		{6,1,6,2,6,3,9,9,6,4},
		{3,6,4,9,6,0,0,9,6,6},
		{6,1,2,3,1,7,3,6,3,3}
	};

	matrix_t matrix2 = {//second 100 mt19937 digits
		{5,0,4,6,9,9,1,6,2,6},
		{1,9,6,5,2,4,4,4,2,6},
		{1,3,1,6,6,3,1,7,1,9},
		{3,6,8,0,0,6,8,6,0,9},
		{9,8,4,5,9,0,6,4,7,0},
		{0,4,2,9,1,3,2,4,1,6},
		{3,8,4,9,0,2,6,5,5,8},
		{2,5,5,9,0,9,5,0,9,2},
		{3,0,6,8,1,6,7,8,2,2},
		{1,3,5,5,0,1,8,3,0,1}
	};

	matrix_t matrixMulExpect = {
		{164,292,275,378,163,270,294,278,182,313},
		{159,209,178,258,159,148,203,201,147,194},
		{151,284,230,332,157,236,230,219,190,280},
		{142,257,231,327,101,148,281,233,137,199},
		{159,264,256,341,173,262,265,267,157,320},
		{165,235,214,281,162,175,230,226,135,216},
		{95,166,137,166,100,113,156,165,77,201},
		{164,228,219,364,155,236,247,235,203,238},
		{148,231,259,261,123,240,274,214,157,207},
		{84,132,149,241,87,184,149,152,105,174}
	};
	/*
		std::cout << "matrixMul test result: " << std::endl;
		for(auto& row : matrixMulFMA(matrix, matrix2)) {
			for(auto& elem : row)
				std::cout << elem << " ";
			std::cout << std::endl;
		}
	*/
	return function(matrix, matrix2) == matrixMulExpect;
}

bool testGaussSeidel() {
	std::vector<std::vector<float> > grid = {
		{1,2,3,4,5},
		{6,7,8,9,8},
		{7,6,5,4,3},
		{2,1,0,1,2},
		{3,4,5,6,7}
	};
	std::vector<std::vector<float> > gridRes = {
		{1,2,3,4,5},
		{6,12.5,14,15,8},
		{7,11,9.5,8.5,3},
		{2,4,3,4,2},
		{3,4,5,6,7}
	};
	/*
	std::cout << "gaussSeidel test-result: " << std::endl;
	for(auto& row : gaussSeidelIteration(grid)) {
		for(auto& elem : row)
			std::cout << elem << " ";
		std::cout << std::endl;
	}
	*/
	return gaussSeidelIteration(grid) == gridRes;
}

template<typename matrix_t, typename F>
void measure(size_t targetSize, std::function<int(size_t)> iterationsFkt, std::function<double(size_t)> opsPerIterationFkt, F function) {
	std::cout << "size, iterations, ms, mflops" << std::endl;

	for(size_t size{8}; size <= targetSize; size *= 2) {
		const size_t iterations = iterationsFkt(size);
		const double opsPerIteration = opsPerIterationFkt(size);
		const double opCount{iterations * opsPerIteration};

		matrix_t matrix(size, typename matrix_t::value_type(size));

		std::mt19937 rng(0);
		std::uniform_real_distribution<float> dist(0.0f, 1000.0f);
		for(auto& row : matrix) for(auto& elem : row) elem = dist(rng);
		/*
		for(size_t x{0}; x < size; ++x)
		for(size_t y{0}; y < size; ++y)
			matrix[x][y] = x + y;
		*/

		std::vector<decltype(matrix)> matrixResult(iterations);

		auto start = std::chrono::high_resolution_clock::now();

		for(size_t i{0}; i < iterations; ++i)
			matrixResult[i] = function(matrix);

		auto stop = std::chrono::high_resolution_clock::now();
		auto nanotime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
		const double mflops{1000.0 * opCount / nanotime};// 1000÷nano == mega

		std::cout << size << ", " << iterations << ", " << nanotime/1000.0/1000.0 << ", " << mflops << std::endl;
	}
}

template<typename matrix_t>
void hmmk() {
	for(size_t times{0}; times < 100; ++times) {
		const size_t size = 512;
		const size_t iterations = 100000000/static_cast<int>(std::pow(size, 2.7)) + 1;
		const double opsPerIteration = std::pow(size, 3)*2;
		const double opCount{iterations * opsPerIteration};

		matrix_t matrix(size, typename matrix_t::value_type(size));

		std::mt19937 rng(0);
		std::uniform_real_distribution<float> dist(0.0f, 1000.0f);
		for(auto& row : matrix) for(auto& elem : row) elem = dist(rng);

		std::vector<decltype(matrix)> matrixResult(iterations);

		auto start = std::chrono::high_resolution_clock::now();

		for(size_t i{0}; i < iterations; ++i)
			matrixResult[i] = matrixMulUnrolled(matrix, matrix);

		auto stop = std::chrono::high_resolution_clock::now();
		auto nanotime = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count();
		const double mflops{1000.0 * opCount / nanotime};// 1000÷nano == mega

		std::cout << size << ", " << iterations << ", " << nanotime/1000.0/1000.0 << ", " << mflops << std::endl;
	}
}

int main() {
	using matrix_t = std::vector<std::vector<float>>;
	using matrix_aligned_t = std::vector<std::vector<float, aligned_allocator<float, 32>>>;

	//hmmk<matrix_aligned_t>();

	//*
	assert(testMatrixMul<matrix_t>(matrixMul<matrix_t>));
	//assert(testMatrixMul<matrix_aligned_t>(matrixMulFMA<matrix_aligned_t>));
	assert(testMatrixMul<matrix_t>(matrixMulRotated<matrix_t>));
	assert(testMatrixMul<matrix_t>(matrixMulTiled<matrix_t>));
	assert(testMatrixMul<matrix_t>(matrixMulUnrolled<matrix_t>));
	assert(testGaussSeidel());
	//*/
	/*
	matrix_aligned_t matrix(512, matrix_aligned_t::value_type(512));

	std::mt19937 rng(0);
	std::uniform_real_distribution<float> dist(0.0f, 1000.0f);
	for(auto& row : matrix) for(auto& elem : row) elem = dist(rng);

	auto res0 = matrixMul(matrix, matrix);
	auto res1 = matrixMulFMA(matrix, matrix);
	for(size_t x{0}; x < 512; ++x) {
		for(size_t y{0}; y < 512; ++y)
			if(std::abs(res0[x][y] - res1[x][y]) != 0
					&& std::abs(res0[x][y] - res1[x][y]) != 8
					&& std::abs(res0[x][y] - res1[x][y]) != 16
					&& std::abs(res0[x][y] - res1[x][y]) != 24
					&& std::abs(res0[x][y] - res1[x][y]) != 32
					&& std::abs(res0[x][y] - res1[x][y]) != 40
					&& std::abs(res0[x][y] - res1[x][y]) != 48) {
				std::cout << "[" << x << " " << y << " " << res0[x][y] << " " << res1[x][y] << " " << std::abs(res0[x][y] - res1[x][y]) << "]";
				std::cout << std::endl;
				for(int i=31; i>=0; --i)
					std::cout << ((*(reinterpret_cast<unsigned int*>(&res0[x][y])) & (1u<<i)) == (1u<<i) ? 1 : 0);
				std::cout << std::endl;
				for(int i=31; i>=0; --i)
					std::cout << ((*(reinterpret_cast<unsigned int*>(&res1[x][y])) & (1u<<i)) == (1u<<i) ? 1 : 0);
				std::cout << std::endl;
			}
	}
	//assert(matrixMul(matrix, matrix) == matrixMulFMA(matrix, matrix));//fires because fma is more precise than normal mmul
	assert(matrixMul(matrix, matrix) == matrixMulRotated(matrix, matrix));
	assert(matrixMul(matrix, matrix) == matrixMulTiled(matrix, matrix));
	assert(matrixMul(matrix, matrix) == matrixMulUnrolled(matrix, matrix));
	*/
	//*
	std::cout << "benching gaussSeidelIteration with different Sizes" << std::endl;
	{
		auto iterationsGaussSeidel = [](size_t size) -> size_t {return 50000000/static_cast<int>(std::pow(size, 2)) + 1;};//reduce iterations by complexity
		auto opsPerIterationGaussSeidel = [](size_t size) -> double {return std::pow(size, 2)*4;};
		auto functionGaussSeidel = [](matrix_t & matrix) -> std::remove_reference<decltype(matrix)>::type {return gaussSeidelIteration(matrix);};
		measure<matrix_t>(16384, iterationsGaussSeidel, opsPerIterationGaussSeidel, functionGaussSeidel);
	}
	std::cout << std::endl;
	//*/
	std::cout << "benching MatrixMul with different Sizes" << std::endl;
	auto iterationsMatrixMul = [](size_t size) -> size_t {return 100000000/static_cast<int>(std::pow(size, 2.7)) + 1;};//reduce iterations by complexity
	auto opsPerIterationMatrixMul = [](size_t size) -> double {return std::pow(size, 3)*2;};
	//*
	{
		auto functionMatrixMul = [](matrix_t & matrix) -> std::remove_reference<matrix_t>::type {return matrixMul(matrix, matrix);};
		measure<matrix_t>(2048, iterationsMatrixMul, opsPerIterationMatrixMul, functionMatrixMul);
	}
	std::cout << std::endl;
	//*/
	//*
	std::cout << "benching MatrixMulFMA with different Sizes" << std::endl;
	{
		auto functionMatrixMulFMA = [](matrix_aligned_t & matrix) -> std::remove_reference<matrix_aligned_t>::type {return matrixMulFMA(matrix, matrix);};
		measure<matrix_aligned_t>(2048, iterationsMatrixMul, opsPerIterationMatrixMul, functionMatrixMulFMA);
	}
	//*
	std::cout << std::endl;
	std::cout << "benching matrixMulRotated with different Sizes" << std::endl;
	{
		auto functionMatrixMul = [](matrix_t & matrix) -> std::remove_reference<matrix_t>::type {return matrixMulRotated(matrix, matrix);};
		measure<matrix_t>(2048, iterationsMatrixMul, opsPerIterationMatrixMul, functionMatrixMul);
	}
	std::cout << std::endl;
	std::cout << "benching matrixMulTiled with different Sizes" << std::endl;
	{
		auto functionMatrixMul = [](matrix_t & matrix) -> std::remove_reference<matrix_t>::type {return matrixMulTiled(matrix, matrix);};
		measure<matrix_t>(2048, iterationsMatrixMul, opsPerIterationMatrixMul, functionMatrixMul);
	}
	std::cout << std::endl;
	//*/
	std::cout << "benching matrixMulUnrolled with different Sizes" << std::endl;
	{
		auto functionMatrixMul = [](matrix_t & matrix) -> std::remove_reference<matrix_t>::type {return matrixMulUnrolled(matrix, matrix);};
		measure<matrix_t>(2048, iterationsMatrixMul, opsPerIterationMatrixMul, functionMatrixMul);
	}
	//*/

	std::cout << "Press ENTER to close";
	std::cin.get();
}
