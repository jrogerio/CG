/*
 * Matrix.h
 *
 *  Created on: 18 de set de 2015
 *      Author: plab
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

template<uint M, uint N, class T>
class Matrix {

private:
	T values[M][N];

public:
	Matrix() {}
	~Matrix() {}

	T valueOn(uint row, uint col) {
		T value = NULL;

		if (row < M && col < N)
			value = values[row][col];

		return value;
	}

	void setValueOn(uint row, uint col, T value) {
		if (row < M && col < N)
			values[row][col] = value;
	}

	Matrix<M, N, T> operator+(Matrix<M, N, T>& other) {
		Matrix<M,N,T> sum;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				sum.values[row][col] = values[row][col] + other.values[row][col];
			}
		}

		return sum;
	}

	template<uint N1>
	Matrix<M, N1, T> operator*(Matrix<N, N1, T>& other) {
		Matrix<M,N1,T> mult;
		T value;

		for (uint row = 0; row < M; ++row) {
			for (uint col = 0; col < N1; ++col) {
				value = 0;

				for (uint n = 0; n < N; ++n) {
					value += values[row][n] * other.valueOn(n, col);
				}

				mult.setValueOn(row, col, value);
			}
		}

		return mult;
	}

	Matrix<M, N, T> operator*(T scalar) {
		Matrix<M,N,T> mult;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				mult.values[row][col] = values[row][col] * scalar;
			}
		}

		return mult;
	}
};



#endif /* SRC_MATRIX_H_ */
