#include <cstddef>

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

#ifndef uint
#define uint unsigned int
#endif

using namespace std;

template<uint M, uint N>
class Matrix {

private:
	double _values[M][N];

public:
	Matrix(){}
	~Matrix(){}

	double valueOn(uint row, uint col) {
		double value = 0;

		if (row < M && col < N)
			value = _values[row][col];

		return value;
	}

	void setValueOn(uint row, uint col, double value) {
		if (row < M && col < N)
			_values[row][col] = value;
	}

	static Matrix<M, M> buildIdentity() {
		Matrix<M,M> matrix;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < M; ++col) {
				matrix.setValueOn(row, col, 0);
			}
		}

		for(int diagonal = 0; diagonal < M; diagonal++) {
			matrix.setValueOn(diagonal, diagonal, 1);
		}

		return matrix;
	}

	Matrix<M, N> operator+(Matrix<M, N> other) {
		Matrix<M,N> sum;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				sum._values[row][col] = _values[row][col] + other._values[row][col];
			}
		}

		return sum;
	}

	template<uint N1>
	Matrix<M, N1> operator*(Matrix<N, N1> other) {
		Matrix<M,N1> mult;
		double value;

		for (uint row = 0; row < M; ++row) {
			for (uint col = 0; col < N1; ++col) {
				value = 0;

				for (uint n = 0; n < N; ++n) {
					value += _values[row][n] * other.valueOn(n, col);
				}

				mult.setValueOn(row, col, value);
			}
		}

		return mult;
	}

	Matrix<M, N> operator*(double scalar) {
		Matrix<M,N> mult;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				mult._values[row][col] = _values[row][col] * scalar;
			}
		}

		return mult;
	}
};



#endif /* SRC_MATRIX_H_ */
