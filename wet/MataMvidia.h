
#ifndef UNTITLED7_MATAMVIDIA_H
#define UNTITLED7_MATAMVIDIA_H


#include "Matrix.h"
#include "Utilities.h"
#include <string>
#include <iostream>

class MataMvidia {
private:
    std::string movieName_;
    std::string author_;
    Matrix* frames_;
    int nFrames_;

public:
    MataMvidia(const std::string& name, const std::string& author,
               const Matrix* frames, int nFrames);

    MataMvidia(const MataMvidia& other); // copy constructor
    MataMvidia& operator=(const MataMvidia& other); // assign
    ~MataMvidia(); // destructor

    MataMvidia(MataMvidia&& other) ;
    MataMvidia& operator=(MataMvidia&& other) ;

    int getLength() const { return nFrames_; }
    Matrix& operator[](int i);
    Matrix& operator[](int i) const;

    // printing
    friend std::ostream& operator<<(std::ostream& os,
                                    const MataMvidia& mv);

    MataMvidia& operator+=(const Matrix& frame);

    MataMvidia& operator+=(const MataMvidia& other);

    friend MataMvidia operator+(const MataMvidia& lhs,
                                const MataMvidia& rhs);
};


#endif //UNTITLED7_MATAMVIDIA_H
