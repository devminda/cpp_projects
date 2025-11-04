#include "matrix.h"

Matrix::Matrix() {
	nRows = 1;
	nCols = 1;
	data = new double* [nRows];
	data[0] = new double[nCols];
	data[0][0] = 7.1;

}

Matrix::Matrix(int m, int n) {
	nRows = m;
	nCols = n;
	data = new double* [nRows];
	for (int i = 0;i < nRows;i++)
		data[i] = new double[nCols](); //for every row, create as many columns as you need

	data[0][0] = 7.1;
}

Matrix::Matrix(int m, int n, double** d) {
	nRows = m;
	nCols = n;
	data = new double* [nRows];
	for (int i = 0;i < nRows; i++)
		data[i] = new double[nCols]; //for every row, create as many columns as you need


	for (int i = 0;i < nRows;i++) //initialize my array
		for (int j = 0;j < nCols;j++)
			data[i][j] = d[i][j];
}

void Matrix::print() {
	for (int i = 0;i < nRows; i++)
		for (int j = 0;j < nCols;j++)
			std::cout << data[i][j] << ((j == nCols - 1) ? "\n" : "\t");


}


//Getters
double Matrix::getData(int i, int j) {
	return data[i][j];
}

int Matrix::getRows() {
	return nRows;
}
int Matrix::getCols() {
	return nCols;
}

//Setters
void Matrix::setData(int i, int j, double newData) {
	data[i][j] = newData;

}

void Matrix::setRows(int newRows) { // Limited capability -- Just sets it
	nRows = newRows;
}

//Assignment operator (overloading)
void Matrix::operator = (Matrix m2) {
	//1. Delete the memory space
	for (int i = 0;i < nRows;i++) {
		delete[] data[i];
	}
	delete[] data;

	//2. Allocate new information
	nRows = m2.getRows();
	nCols = m2.getCols();

	data = new double* [nRows];
	for (int i = 0;i < nRows;i++) {
		data[i] = new double[nCols];
	}

	//3. Copy the m2 data
	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols; j++) {
			data[i][j] = m2.getData(i, j);
		}
	}

}

Matrix Matrix::operator+(Matrix m2) {
	Matrix newmatrix = m2;
	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols;j++) {
			newmatrix.setData(i, j, m2.getData(i, j) + data[i][j]);
		}

	}

	return newmatrix;
}

Matrix Matrix::operator*(Matrix m2) {

	Matrix newmatrix(nRows, m2.getCols());
	for (int i = 0; i < nRows;i++) {
		for (int j = 0;j < m2.getCols(); j++) {
			double sumproduct = 0;
			for (int k = 0;k < nCols;k++)
				sumproduct += data[i][k] * m2.data[k][j];
			newmatrix.data[i][j] = sumproduct;
		}
	}
	return newmatrix;
}
std::vector<double> Matrix::operator*(const std::vector<double>& v) {
	std::vector<double> y(nRows, 0.0);
	
	for (int i = 0;i < nRows;i++) {
		double s=0.0;
		int k = 0;
		for (int j = 0; j < nCols;j++) {
			s+=data[i][j] * v[k];
			k++;
		}
		y[i] = s;
		
	}
	return y;
}
double Matrix::determinant() {

	// Recursions ending conditions
	if (nRows == 1)
		return data[0][0];
	else if (nRows == 2)
		return data[0][0] * data[1][1] - data[0][1] * data[1][0];
	else {
		double det = 0;
		int i = 0;
		for (int j = 0;j < nCols;j++) {
			det += cofactor(i, j) * data[0][j] * minor(i, j);
		}
		return det;
	}
}
double Matrix::cofactor(int i, int j) {
	return pow(-1, i + j);
}

double Matrix::minor(int i, int j) {

	Matrix newmatrix(nRows - 1, nCols - 1);
	int rd, cd;
	for (int i1 = 0; i1 < nRows; i1++) {
		if (i1 == i) {
			continue;
		}
		if (i1 < i) {
			rd = i1;
		}
		else {
			rd = i1 - 1;
		}
		for (int j1 = 0; j1 < nCols;j1++) {
			if (j1 == j) {
				continue;
			}
			if (j1 < j) {
				cd = j1;
			}
			else {
				cd = j1 - 1;
			}
			newmatrix.setData(rd, cd, data[i1][j1]);
		}
	}
	return newmatrix.determinant();
}


// return type  --- class name --- functionality (arguments)
Matrix Matrix::transpose_external() {
	Matrix newmatrix(nCols, nRows);

	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols;j++) {
			newmatrix.data[j][i] = data[i][j];
		}
	}

	return newmatrix;
}

void Matrix::transpose() {
	Matrix newmatrix(nCols, nRows); // remember: the transpose has #rows=original's #cols and #cols=original's #rows

	for (int i = 0;i < nRows;i++) {
		for (int j = 0;j < nCols;j++) {
			newmatrix.data[j][i] = data[i][j];
		}
	}

	for (int i = 0;i < nRows;i++)
		delete[] data[i];

	delete[] data;

	int oldnRows = nRows; // 4
	int oldnCols = nCols; // 3

	nRows = nCols;
	nCols = oldnRows;

	data = new double* [nRows];
	for (int i = 0;i < nRows;i++) {
		data[i] = new double[nCols];
		for (int j = 0;j < nCols;j++)
			data[i][j] = newmatrix.data[i][j];
	}

}

void Matrix::read_data(std::string s) {
	std::ifstream f(s);
	f >> nRows >> nCols;
	for (int i = 0;i < nRows;i++)
		for (int j = 0;j < nCols;j++)
			f >> data[i][j];
}

std::vector<std::vector<int>> combos(int n, int r) {
	std::vector<std::vector<int>> result;
	std::vector<bool> v(n);
	std::fill(v.end() - r, v.end(), true);
	do {
		std::vector<int> current_result;
		for (int i = 0;i < n;i++)
			if (v[i])
				current_result.push_back(i);
		result.push_back(current_result);
	} while (std::next_permutation(v.begin(), v.end()));
	std::reverse(result.begin(), result.end());

	return result;
}

int Matrix::rank() {
	int m = getRows();
	int active_cols=getCols();	
	int i = 0;

	while (i < m && i < active_cols) {
		if (std::abs(data[i][i]) != 0.0) {
			double piv = data[i][i];

			for (int k = i + 1; k < m; k++) {
				if (std::abs(data[k][i]) != 0.0) {
					double fac = data[k][i] / piv;

					for (int j = i;j < active_cols;j++) {
						data[k][j] -= fac * data[i][j];

						if (std::abs(data[k][j]) == 0.0) {
							data[k][j] = 0;
						}
					}
				}

			}
			i += 1;
			continue;
		}
		int swap_row = -1;
		for (int k = i + 1;k < m;k++) {
			if (std::abs(data[k][i]) > 0.0) {
				swap_row = k;
				break;
			}
		}
		if (swap_row != -1) {
			std::swap(data[i], data[swap_row]);

			continue;

		}
		int last = active_cols - 1;
		
		
		for (int r = 0;r < m;r++) {
			std::swap(data[r][i], data[r][last]);
			
		}
		--active_cols;

	}
	return i;

}

Matrix Matrix::inverse() {
	// Create a temporary matrix to disallow altering of the main matrix
	Matrix newmatrix(getRows(), getCols());
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			newmatrix.setData(i, j, data[i][j]);
		}
	}

	//get determinant
	double det = newmatrix.determinant();
	//check if the determinant is not equal to zero
	if (det == 0) {
		std::cout << "The Matrix doesn't have an inverse" << std::endl;
		return newmatrix;
	}
	

	//calculate cofactor matrix
	Matrix cofactor_matrix(getRows(), getCols());

	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			cofactor_matrix.setData(i, j, cofactor(i, j)*newmatrix.minor(i,j));
		}
	}

	//calculate the transpose of cofactor matriX
	cofactor_matrix.transpose();
	//Multiple the 1/determinant * cofactor matrix(t)
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			newmatrix.setData(i, j, (1/det)*cofactor_matrix.getData(i,j));
		}
	}
	return newmatrix;
}

//This function will check if there are any negative results 
bool Matrix::check_negatives(const std::vector<double>& v) {
	for (double val : v) {
		if (val < 0.0) {
			return true;
		}
		
	}
	return false;
}
void Matrix::getAllBFS(std::vector<double> rhs) {
	Matrix newmatrix(getRows(), getCols());
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			newmatrix.setData(i, j, data[i][j]);
		}
	}
	Matrix rankNewmatrix(getRows(), getCols());
	for (int i = 0; i < nRows; i++) {
		for (int j = 0; j < nCols; j++) {
			rankNewmatrix.setData(i, j, data[i][j]);
		}
	}
		
	//Calculate the rank of the matrix
	int rank = rankNewmatrix.rank();
	if (rank < nRows) {
		std::cout << "No BFS: rank(A) < number of rows\n";
		return;
	}
	auto colCombos = combos(nCols, nRows);

	int infeasible_count = 0;
	int det_count = 0;
	for (const auto& combo : colCombos) {
		Matrix smallM(nRows, nRows);
		for (int j = 0; j < nRows; ++j) {
			for (int k = 0; k < nRows;++k) {
				
				smallM.setData(j, k, data[j][combo[k]]);
			}
		}
		
		Matrix detM = smallM;
		double det = detM.determinant();
		if (det == 0) {
			det_count++;
			continue;
		}
		
		Matrix inverse_m = smallM.inverse();
		
		std::vector<double> ans;
		ans = inverse_m * rhs;
        
		bool check = check_negatives(ans);
		if (check==true) {
			infeasible_count ++;
			continue;
		}
		
		std::vector<double> vec(nCols, 0.0);

		for (int q = 0; q < rank; ++q) {
			//std::cout << combo[q] << std::endl;
			vec[combo[q]] = ans[q];

		}
		
		std::cout << "(";
		for (size_t i=0 ;i< vec.size();i++) {
			std::cout << vec[i];
			if (i != vec.size() - 1) {
				std::cout << ", ";

			}
			else
			{
				continue;
			}
		}
		std::cout << ")" << std::endl;
		
	}
	
	
	if (infeasible_count + det_count  == colCombos.size()) {
		std::cout << "No feasible solutions" << std::endl;
	}
	
	
}



