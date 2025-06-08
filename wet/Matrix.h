
#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

class Matrix {
private:
    int* array;
    int rows_m;
    int cols_n;

    void checkBounds(int rows, int cols) const;

public:
    Matrix(int rows, int cols, int value=0);

    Matrix();

    Matrix(const Matrix& other);

    Matrix& operator=(const Matrix& other);

    ~Matrix(); // destructor

    int& operator()(int rows, int cols);
    const int& operator()(int rows, int cols) const;

    // private members getters
    int getRows() const { return rows_m; }
    int getCols() const { return cols_n; }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);
    Matrix& operator*=(const Matrix& rhs);    // matrix × matrix
    Matrix& operator*=(int scalar);           // matrix × scalar

    friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
    friend Matrix operator*(const Matrix& lhs, const Matrix& rhs); // mat × mat
    friend Matrix operator*(const Matrix& m, int scalar);          // mat × k
    friend Matrix operator*(int scalar, const Matrix& m);          // k × mat
    friend Matrix operator-(const Matrix& m);
    friend bool operator==(const Matrix& a, const Matrix& b);
    friend bool operator!=(const Matrix& a, const Matrix& b);

    Matrix transpose() const;
    Matrix rotateClockwise() const;
    Matrix rotateCounterClockwise() const;

    double calcFrobeniusNorm() const;

    int  calcDeterminant() const;
    static int CalcDeterminant(const Matrix& m); // wrapper
};



#endif //MATRIX_H
