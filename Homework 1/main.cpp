// Homework1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "matrix.h"

int main()
{
    // This next part is meant to show how the combos(int, int) functionality works. Please uncomment at will to observe and use.
//    std::vector<std::vector<int>> c=combos(5,3);
//    std::vector<std::vector<int>>::iterator it=c.begin();
//    for(it=c.begin();it!=c.end();it++){
//        std::vector<int>::iterator it2;
//        for(it2=(*it).begin();it2!=(*it).end();it2++)
//            std::cout << *it2 << " ";
//        std::cout << std::endl;
//    }

    //// Define a matrix m1 that is 3x3
    Matrix m1(2, 5);
    Matrix rank_m(2, 5);
    // Read data from the file called matrix.dat.
    // Please make sure that the file you want to read from is in a proper location.
    m1.read_data("matrix3.dat");
    for (int i = 0;i < m1.getRows();i++) {
        for (int j = 0;j < m1.getCols();j++) {
            rank_m.setData(i, j, m1.getData(i, j));
        }
    }
    //m1.print();
    std::cout << "The Matrix is :" << std::endl;
    rank_m.print();
    int matrix_rank = rank_m.rank();
    std::cout << "The rank of the matrix is " << matrix_rank << std::endl;

    std::cout << "Enter " << matrix_rank << " Values for the rhs" << std::endl;
    std::vector<double> rhs; // right-hand side vector (b, in Ax=b)
    for (int i = 0;i < matrix_rank;i++) {
        double inp;
        std::cin >> inp; // accept input from the user
        rhs.push_back(inp); // create the right-hand side vector b
    }
    std::cout << "All basic feasible solutions are: " << std::endl;
    
    m1.getAllBFS(rhs); // prints all basic feasible solutions each in one line
    // For example, if there are three basic feasible solutions (2, 1, 0), (0, 3, 3), (1, 0, 1), it will print:
    // (2, 1, 0)
    // (0, 3, 3)
    // (1, 0, 1)
    
    return 0;
}

