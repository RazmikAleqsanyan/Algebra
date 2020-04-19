#include <iostream>
#include "Matrix.h"

std::ostream& operator<<(std::ostream& ost, const Matrix& m) {
	for (int i = 0; i < m.m_height; ++i) {
		for (int j = 0; j < m.m_length; ++j) {
			std::cout << m.m_data[i][j] << " ";
		}
		std::cout << std::endl;
	}
	return ost;
}

std::istream& operator>>(std::istream& ist, Matrix& m) {
	int height = 0, length = 0;
	std::cin >> height >> length; 

	if (height != m.m_height && length != m.m_length) {
		for (int i = 0; i < m.m_height; ++i) {
			delete[] m.m_data[i];
		}
		delete[] m.m_data;
		
		m.m_data = new int*[height];
		for (int i = 0; i < height; ++i) {
			m.m_data[i] = new int[length];
		}
		m.m_height = height;
		m.m_length = length;
	}

	for (int i = 0; i < m.m_height; ++i) {
		for (int j = 0; j < m.m_length; ++j) {
			std::cin >> m.m_data[i][j];
		}
	}
	return ist;
}


Matrix::Matrix(const Matrix& m)
	: m_data(nullptr)
	, m_height(m.m_height)
	, m_length(m.m_length)
{
	m_data = new int* [m_height];
	for (int i = 0; i < m_height; ++i) {
		m_data[i] = new int[m_length];
	}
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_length; ++j) {
			m_data[i][j] = m.m_data[i][j];
		}
	}
}

Matrix::Matrix(int** arr, const int length, const int height) 
	: m_data(nullptr)
	, m_height(height)
	, m_length(length)
{
	int** tmp = new int* [m_height];
	for (int i = 0; i < m_height; ++i) {
		tmp[i] = new int[m_length];
	}
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_length; ++j) {
			tmp[i][j] = arr[i][j];
		}
	}
	m_data = tmp;
}

Matrix& Matrix::operator=(const Matrix& m) {
	if(this != &m) {
		if (m.m_height != m_height && m.m_length != m_length) {
			for (int i = 0; i < m_height; ++i) {
				delete[] m_data[i];
			}
			delete[] m_data;
			m_height = m.m_height;
			m_length = m.m_length;
			m_data = new int* [m_height];
			for (int i = 0; i < m_height; ++i) {
				m_data[i] = new int[m_length];
			}
		}
		for (int i = 0; i < m_height; ++i) {
			for (int j = 0; j < m_length; ++j) {
				m_data[i][j] = m.m_data[i][j];
			}
		}
	}
	return *this;
}

Matrix::~Matrix() {
	for (int i = 0; i < m_height; ++i) {
		delete[] m_data[i];
	}
	delete[] m_data;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if (m_length == m.m_length && m_height == m.m_height) {
		for (int i = 0; i < m_height; ++i) {
			for (int j = 0; j < m_length; ++j) {
				m_data[i][j] += m.m_data[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
	if (m_length == m.m_length && m_height == m.m_height) {
		for (int i = 0; i < m_height; ++i) {
			for (int j = 0; j < m_length; ++j) {
				m_data[i][j] -= m.m_data[i][j];
			}
		}
	}
	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	if (m_length == m.m_height) {
		int** tmp = new int* [m_height];
		for (int i = 0; i < m_height; ++i) {
			tmp[i] = new int[m.m_length];
		}
		for (int i = 0; i < m.m_length; ++i) {
			for (int j = 0; j < m_height; ++j) {
				tmp[j][i] = m_data[j][0] * m.m_data[0][i];
				for (int k = 1; k < m_length; ++k) {
					tmp[j][i] += m_data[j][k] * m.m_data[k][i];
				}
			}
		}

		for (int i = 0; i < m_height; ++i) {
			delete[] m_data[i];
		}
		delete[] m_data;

		m_length = m.m_length;
		m_data = tmp;
	}
	return *this;
}

Matrix& Matrix::operator*=(int n) {
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_length; ++j) {
			m_data[i][j] *= n;
		}
	}
	return *this;
}

void Matrix::SwapColumns(int n1, int n2) {
	if (n1 < 0 || n2 < 0 || n1 >= m_height || n2 >= m_height) {
		return;
	}
	int tmp = 0;
	for (int i = 0; i < m_height; ++i) {
		tmp = m_data[n1][i];
		m_data[n1][i] = m_data[n2][i];
		m_data[n2][i] = tmp;
	}
}

void Matrix::SwapRows(int n1, int n2) {
	if (n1 < 0 || n2 < 0 || n1 >= m_length || n2 >= m_length) {
		return;
	}
	int tmp = 0;
	for (int i = 0; i < m_length; ++i) {
		tmp = m_data[i][n1];
		m_data[i][n1] = m_data[i][n2];
		m_data[i][n2] = tmp;
	}
}

void Matrix::AddCulumns(int n1, int n2, int coeff) {       // add column to another multiplied by some number 
	if (n1 < 0 || n2 < 0 || n1 >= m_height || n2 >= m_height || coeff == 0) {
		return;
	}
	for (int i = 0; i < m_height; ++i) {
		m_data[n1][i] += m_data[n2][i] * coeff;
	}
}

void Matrix::AddRows(int n1, int n2, int coeff) {		// add row to another multiplied by some number 	
	if (n1 < 0 || n2 < 0 || n1 >= m_length || n2 >= m_length || coeff == 0) {
		return;
	}
	int tmp = 0;
	for (int i = 0; i < m_length; ++i) {
		m_data[i][n1] += m_data[i][n2] * coeff;
	}
}

void Matrix::ChangeSignOfColumn(int n) {		  // warning it changes the matrix
	for (int i = 0; i < m_length; ++i) {
		m_data[n][i] = -m_data[n][i];
	}
}

void Matrix::ChangeSignOfRow(int n) {			  // warning it changes the matrix
	for (int i = 0; i < m_length; ++i) {
		m_data[i][n] = -m_data[i][n];
	}
}
	
Matrix& Matrix::transpose() {
	int** tmp = new int* [m_length];
	for (int i = 0; i < m_length; ++i) {
		tmp[i] = new int[m_height];
	}
	for (int i = 0; i < m_length; ++i) {
		for (int j = 0; j < m_height; ++j) {
			tmp[i][j] = m_data[j][i];
		}
	}
	return *this;
}

bool Matrix::operator==(const Matrix& m) const {
	if (m_length != m.m_length || m_height != m.m_height) {
		return false;
	}
	for (int i = 0; i < m_height; ++i) {
		for (int j = 0; j < m_length; ++j) {
			if (m_data[i][j] != m.m_data[i][j]) {
				return false;
			}
		}
	}
	return true;
}

///Not member
Matrix& operator+(Matrix m1, const Matrix& m2) {
	return m1 += m2;
}

Matrix& operator-(Matrix m1, const Matrix& m2) {
	return m1 -= m2;
}

Matrix& operator*(int n, Matrix m) {
	return m *= n;
}

Matrix& operator*(Matrix m, int n) {
	return m *= n;
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
	return !(m1 == m2);
}

int determinant(Matrix);
Matrix& inverse();
int Rank(Matrix);