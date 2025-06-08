#include "MataMvidia.h"

MataMvidia::MataMvidia(const std::string& name, const std::string& author,
                       const Matrix* frames, int nFrames)
        : movieName_(name),
          author_(author),
          frames_(nullptr),
          nFrames_(nFrames)
{
    // no empty movies
    if (nFrames_ <= 0)
        exitWithError(MatamErrorType::OutOfBounds);

    frames_ = new Matrix[nFrames_];
    for (int i = 0; i < nFrames_; ++i)
        frames_[i] = frames[i];
}

MataMvidia::MataMvidia(const MataMvidia& other)
        : MataMvidia(other.movieName_, other.author_,
            other.frames_, other.nFrames_) {}

MataMvidia& MataMvidia::operator=(const MataMvidia& other){
    if (this == &other) return *this;
    delete[] frames_;
    movieName_ = other.movieName_;
    author_ = other.author_;
    nFrames_ = other.nFrames_;
    frames_ = new Matrix[nFrames_];
    for (int i = 0; i < nFrames_; ++i)
        frames_[i] = other.frames_[i];
    return *this;
}

MataMvidia::~MataMvidia(){
    delete[] frames_;
}

MataMvidia::MataMvidia(MataMvidia&& other)
        : movieName_(std::move(other.movieName_)),
          author_(std::move(other.author_)),
          frames_(other.frames_),
          nFrames_(other.nFrames_)
{
    other.frames_ = nullptr;
    other.nFrames_= 0;
}

MataMvidia& MataMvidia::operator=(MataMvidia&& other)
{
    if (this == &other) return *this;
    delete[] frames_;
    movieName_ = std::move(other.movieName_);
    author_ = std::move(other.author_);
    frames_ = other.frames_;
    nFrames_ = other.nFrames_;
    other.frames_ = nullptr;
    other.nFrames_= 0;
    return *this;
}


Matrix& MataMvidia::operator[](int i)
{
    if (i < 0 || i >= nFrames_) exitWithError(MatamErrorType::OutOfBounds);
    return frames_[i];
}

Matrix& MataMvidia::operator[](int i) const
{
    if (i < 0 || i >= nFrames_) exitWithError(MatamErrorType::OutOfBounds);
    return frames_[i];
}

MataMvidia& MataMvidia::operator+=(const Matrix& frame)
{
    /* allocate new array with +1 size and copy */
    Matrix* newFrames = new Matrix[nFrames_ + 1];
    for (int i = 0; i < nFrames_; ++i){
        newFrames[i] = frames_[i];
    }
    newFrames[nFrames_] = frame;

    delete[] frames_;
    frames_ = newFrames;
    ++nFrames_;
    return *this;
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& other)
{
    int newLen = nFrames_ + other.nFrames_;
    Matrix* newFrames = new Matrix[newLen];

    for (int i = 0; i < nFrames_; ++i){
        newFrames[i] = frames_[i];
    }

    for (int i = 0; i < other.nFrames_; ++i)
        newFrames[nFrames_ + i] = other.frames_[i];

    delete[] frames_;
    frames_ = newFrames;
    nFrames_ = newLen;
    return *this;
}

MataMvidia operator+(const MataMvidia& lhs, const MataMvidia& rhs)
{
    int total = lhs.nFrames_ + rhs.nFrames_;
    Matrix* tmp = new Matrix[total];

    for (int i = 0; i < lhs.nFrames_; ++i)
        tmp[i] = lhs.frames_[i];

    for (int i = 0; i < rhs.nFrames_; ++i)
        tmp[lhs.nFrames_ + i] = rhs.frames_[i];

    MataMvidia res(lhs.movieName_, lhs.author_, tmp, total);
    delete[] tmp;
    return res;
}




std::ostream& operator<<(std::ostream& os, const MataMvidia& mv)
{
    os << "Movie Name: " << mv.movieName_ << std::endl;
    os << "Author: "     << mv.author_    << std::endl
       << std::endl;

    for (int f = 0; f < mv.nFrames_; ++f) {
        os << "Frame " << f << ":" << std::endl;
        os << mv.frames_[f] << std::endl;
    }

    os << "-----End of Movie-----" << std::endl;
    return os;
}



