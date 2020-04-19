#include <iostream>

#pragma once

class Matrix {
	friend std::ostream& operator<<(std::ostream&, const Matrix&);
	friend std::istream& operator>>(std::istream&, Matrix&);
public:
	Matrix() : m_data(nullptr), m_height(0), m_length(0) {}
	Matrix(const Matrix&);
	Matrix(int**, const int, const int);
	Matrix& operator=(const Matrix&);
	~Matrix();

	Matrix& operator+=(const Matrix&);
	Matrix& operator-=(const Matrix&);
	Matrix& operator*=(const Matrix&);
	Matrix& operator*=(int);
	void SwapColumns(int, int);
	void SwapRows(int, int);
	void AddCulumns(int, int, int);       // add column to another multiplied by some number 
	void AddRows(int, int, int);		  // add row to another multiplied by some number 	
	void ChangeSignOfColumn(int);		  // warning it changes the matrix
	void ChangeSignOfRow(int);			  // warning it changes the matrix
	Matrix& transpose();
	int operator()(int i, int j) const { return m_data[i][j]; }
	bool operator==(const Matrix&) const;
	int getLength() const { return m_length; }
	int getHeight() const { return m_height; }
private:
	int** m_data;
	int m_height;
	int m_length;
};

Matrix& operator+(Matrix, const Matrix&);
Matrix& operator-(Matrix, const Matrix&);
Matrix& operator*(int, Matrix);
Matrix& operator*(Matrix, int);
bool operator!=(const Matrix&, const Matrix&);

int determinant(Matrix);
Matrix& inverse();
int Rank(Matrix);