
#include "Matrix.h"
#include "Utilities.h"
#include <cmath>

Matrix::Matrix(int rows, int cols, int value) : array(nullptr), rows_m(rows), cols_n(cols){

    if(rows <= 0 || cols <= 0) {
        rows_m = cols_n = 0;
        return;
    }
    array = new int[rows_m*cols_n];
    for(int i = 0; i < rows_m*cols_n; ++i) {
        array[i] = value;
    }
}


Matrix::Matrix() : array(nullptr), rows_m(0), cols_n(0) {}

Matrix::Matrix(const Matrix& other) : array(nullptr), rows_m(other.rows_m), cols_n(other.cols_n){
    if(other.array){
        array = new int[rows_m * cols_n];
        for(int i=0; i < rows_m * cols_n; ++i){
            array[i] = other.array[i];
        }
    }
}


// assignment operator
Matrix& Matrix::operator=(const Matrix& other){

    if(this == &other) return *this;

    int* newData = nullptr;
    if(other.array) {
        newData = new int[other.rows_m * other. cols_n];
        for(int i=0; i < other.rows_m * other.cols_n; ++i){
            newData[i] = other.array[i];
        }
    }

    delete[] array;
    array = newData;
    rows_m = other.rows_m;
    cols_n = other.cols_n;
    return *this;
}

// destructor
Matrix::~Matrix(){
    delete[] array;
}


void Matrix::checkBounds(int rows, int cols) const {
    if(rows < 0 || rows >= rows_m || cols < 0 || cols >= cols_n){
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

int& Matrix::operator()(int rows, int cols){
    checkBounds(rows, cols);
    return array[rows* cols_n + cols];
}

const int& Matrix::operator()(int row, int col) const
{
    checkBounds(row, col);
    return array[row * cols_n + col];
}




std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    int rows = m.getRows();
    int cols = m.getCols();
    for (int i = 0; i < rows; ++i) {
        os << '|';
        for (int j = 0; j < cols; ++j) {
            os << m(i, j) << '|';
        }
        os << std::endl;
    }
    return os;
}




static int idx(int r, int c, int width) {
    return r * width + c;
}

static void sizeMatch(int r1, int c1, int r2, int c2)
{
    if (r1 != r2 || c1 != c2)
        exitWithError(MatamErrorType::UnmatchedSizes);
}


Matrix& Matrix::operator+=(const Matrix& rhs){
    sizeMatch(rows_m, cols_n, rhs.rows_m, rhs.cols_n);
    for (int i = 0; i < rows_m * cols_n; ++i)
        array[i] += rhs.array[i];
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs){
    sizeMatch(rows_m, cols_n, rhs.rows_m, rhs.cols_n);
    for (int i = 0; i < rows_m * cols_n; ++i)
        array[i] -= rhs.array[i];
    return *this;
}


Matrix& Matrix::operator*=(const Matrix& rhs){
    *this = (*this) * rhs;
    return *this;
}

Matrix& Matrix::operator*=(int scalar){
    for (int i = 0; i < rows_m * cols_n; ++i)
        array[i] *= scalar;
    return *this;
}

// --- now friend functions -----------------

Matrix operator+(const Matrix& lhs, const Matrix& rhs){
    sizeMatch(lhs.rows_m, lhs.cols_n, rhs.rows_m, rhs.cols_n);
    Matrix res(lhs.rows_m, lhs.cols_n);
    for (int i = 0; i < lhs.rows_m * lhs.cols_n; ++i)
        res.array[i] = lhs.array[i] + rhs.array[i];
    return res;
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
    sizeMatch(lhs.rows_m, lhs.cols_n, rhs.rows_m, rhs.cols_n);
    Matrix res(lhs.rows_m, lhs.cols_n);
    for (int i = 0; i < lhs.rows_m * lhs.cols_n; ++i)
        res.array[i] = lhs.array[i] - rhs.array[i];
    return res;
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
    if (lhs.cols_n != rhs.rows_m)
        exitWithError(MatamErrorType::UnmatchedSizes);

    Matrix res(lhs.rows_m, rhs.cols_n, 0);
    for (int i = 0; i < lhs.rows_m; ++i)
        for (int k = 0; k < lhs.cols_n; ++k) {
            int a = lhs.array[idx(i, k, lhs.cols_n)];
            for (int j = 0; j < rhs.cols_n; ++j)
                res.array[idx(i, j, res.cols_n)] +=
                        a * rhs.array[idx(k, j, rhs.cols_n)];
        }
    return res;
}

Matrix operator*(const Matrix& m, int scalar)
{
    Matrix res(m.rows_m, m.cols_n);
    for (int i = 0; i < m.rows_m * m.cols_n; ++i)
        res.array[i] = m.array[i] * scalar;
    return res;
}

Matrix operator*(int scalar, const Matrix& m){
    return m*scalar;
}

Matrix operator-(const Matrix& m)
{
    Matrix res(m.rows_m, m.cols_n);
    for (int i = 0; i < m.rows_m * m.cols_n; ++i){
        res.array[i] = -m.array[i];
    }
    return res;
}


bool operator==(const Matrix& a, const Matrix& b)
{
    if (a.rows_m != b.rows_m || a.cols_n != b.cols_n){
        return false;
    }

    for (int i = 0; i < a.rows_m * a.cols_n; ++i) {
        if (a.array[i] != b.array[i]){
            return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& a, const Matrix& b) {
    return !(a == b);
}

Matrix Matrix::transpose() const
{
    Matrix res(cols_n, rows_m);
    for (int r = 0; r < rows_m; ++r)
        for (int c = 0; c < cols_n; ++c)
            res.array[c * res.cols_n + r] = array[r * cols_n + c];
    return res;
}

Matrix Matrix::rotateClockwise() const
{
    Matrix res(cols_n, rows_m);
    for (int r = 0; r < rows_m; ++r)
        for (int c = 0; c < cols_n; ++c)
            res.array[c * res.cols_n + (rows_m - 1 - r)] = array[r * cols_n + c];
    return res;
}

Matrix Matrix::rotateCounterClockwise() const
{
    Matrix res(cols_n, rows_m);
    for (int r = 0; r < rows_m; ++r)
        for (int c = 0; c < cols_n; ++c)
            res.array[(cols_n - 1 - c) * res.cols_n + r] = array[r * cols_n + c];
    return res;
}


double Matrix::calcFrobeniusNorm() const
{
    double sum = 0.0;
    for (int i = 0; i < rows_m * cols_n; ++i) {
        double val = array[i];
        sum += val * val;
    }
    return std::sqrt(sum);
}

static int detRecursive(const int* arr, int n) {
    if (n == 1) {
        return arr[0];
    }
    if (n == 2) {
        // mikre prati: det(A) = ad - bc
        return arr[0] * arr[3] - arr[1] * arr[2];
    }
    int result = 0;
    int sign = 1;
    for (int j = 0; j < n; ++j) {
        int coeff = arr[j];  // element (0,j)
        int* sub = new int[(n-1)*(n-1)];
        int idx = 0;
        for (int r = 1; r < n; ++r) {
            for (int c = 0; c < n; ++c) {
                if (c == j) continue;
                sub[idx++] = arr[r*n + c];
            }
        }
        int subdet = detRecursive(sub, n-1);
        delete[] sub;
        result += sign * coeff * subdet;
        sign = -sign;
    }
    return result;
}

int Matrix::calcDeterminant() const {
    if (rows_m <= 0 || cols_n <= 0 || rows_m != cols_n) {
        exitWithError(MatamErrorType::NotSquareMatrix);
    }
    return detRecursive(array, rows_m);
}

// wrapper for the tests to work
int Matrix::CalcDeterminant(const Matrix& m) {
    return m.calcDeterminant();
}























