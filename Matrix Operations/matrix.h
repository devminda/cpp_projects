#ifndef matrix_hpp
#define matrix_hpp

#include <iostream>
#include <random>

#include <stdio.h>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

class Matrix {
private:
	//data
	int nRows;
	int nCols;
	double** data;// because it is 2D array, we need a pointer to a pointer

public: // data or methods that interact with the user
	//methods
	//1. Constructors
	Matrix();
	Matrix(int, int);
	Matrix(int, int, double**);

	//2. Getters
	double getData(int, int);
	int getRows();
	int getCols();
	//3. Setters
	void setRows(int newRows);
	void setData(int, int, double newData);

	//4. Auxiliary and core functionality
	void print();
	void transpose(); // transpose
	Matrix transpose_external(); // second way to transpose

	void operator = (Matrix m2); //m = m2
	Matrix operator+(Matrix m2);
	Matrix operator *(Matrix m2);
	std::vector<double> operator*(const std::vector<double>& v);

	double cofactor(int i, int j);
	double minor(int i, int j);
	double determinant();

	void read_data(std::string s);

	int rank();
	Matrix inverse();

	void getAllBFS(std::vector<double> rhs);
	bool check_negatives(const std::vector<double>& v);

	//5. Destructor



};
std::vector<std::vector<int>> combos(int n, int r);

#endif /*matrix_hpp */#pragma once
