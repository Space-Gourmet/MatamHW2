//
// Created by david on 01/06/2025.
//

#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
private:
    int* array;
    int rows;
    int cols;

public:
    Matrix(int rows, int cols, int value=0);

    Matrix();

    Matrix(const Matrix& other);

    Matrix& operator=(const Matrix& other);


}

#endif //MATRIX_H
