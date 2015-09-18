/*
 * Matrix.h
 *
 *  Created on: 18 de set de 2015
 *      Author: plab
 */

#ifndef SRC_MATRIX_H_
#define SRC_MATRIX_H_

template<uint M, uint N, typename T>
class Matrix {

private:
	T values[M][N];

public:
	Matrix() {}
	~Matrix() {}

	friend Matrix<M, N, T> operator+(const Matrix<M, N, T>& first, const Matrix<M, N, T>& other) {
		Matrix<M,N,T> sum;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				sum.values[row][col] = first.values[row][col] + other.values[row][col];
			}
		}

		return sum;
	}

	friend Matrix<M, N, T> operator*(const Matrix<M, N, T>& first, const Matrix<M, N, T>& other) {
		Matrix<M,N,T> sum;

		for (int row = 0; row < M; ++row) {
			for (int col = 0; col < N; ++col) {
				sum.values[row][col] = first.values[row][col] * other.values[row][col];
			}
		}

		return sum;
	}

	friend Matrix<M, N, T> operator*(const Matrix<M, N, T>& first, const T& scalar) {
			Matrix<M,N,T> sum;

			for (int row = 0; row < M; ++row) {
				for (int col = 0; col < N; ++col) {
					sum.values[row][col] = first.values[row][col] * scalar;
				}
			}

			return sum;
		}


	T valueOn(uint row, uint col) {
		int value = -1;

		if (row < M && col < N)
			value = *values[row, col];

		return value;
	}

	void setValueOn(uint row, uint col, T value) {
		if (row < M && col < N)
			values[row][col] = value;
	}
};



#endif /* SRC_MATRIX_H_ */
