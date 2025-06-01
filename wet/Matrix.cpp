//
// Created by david on 01/06/2025.
//
#include "Matrix.h"

Matrix(int rows, int cols, int value=0){

    if(rows*cols == 0) {
        this->array = nullptr;
        this.rows = 0;
        this.cols = 0;
        return;}
    this->rows = rows;
    this->cols = cols;
    this->array = new int[rows*cols];
    for(int i = 0; i < rows*cols; i++) {
    this->array[i] = value;
    }
}
Matrix(){
    this->rows = 0;
    this->cols = 0;
    this->array = nullptr;
}
Matrix(const Matrix& other){
    this->rows = other.rows;
    this->cols = other.cols;
    this->array = new int[rows*cols];
    for(int i = 0; i < rows*cols; i++) {
    this->array[i] = other.array[i];
    }
}
Matrix& operator=(const Matrix& other){
    this->rows = other.rows;
    this->cols = other.cols;
    if(other.array == nullptr) {
        delete[] this->array;
        this->array = nullptr;
    }
    else{
        delete[] this->array;
        this->array = new int[rows*cols];
        for(int i = 0; i < rows*cols; i++) {
            this->array[i] = other.array[i];
        }
    }
    return *this;
}


