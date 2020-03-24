#include <iostream>
#include "Matrix.h"

Matrix::Matrix ():
    rows_ (1),
    cols_ (1),
    data_ (new int* [rows_])
    {
        for (int i = 0; i < rows_; i++)
        {
            data_ [i] = new int [cols_];
        }
    }

Matrix::Matrix (const size_t rows, const size_t cols):
    rows_ (rows),
    cols_ (cols),
    data_ (new int* [rows_])
    {
        for (int i = 0; i < rows_; i++)
        {
            data_ [i] = new int [cols_];
        }
    }

Matrix::~Matrix ()
{
    for (int i = 0; i < rows_; i++)
    {
        delete [] data_ [i];
    }
    delete [] data_;
}

Proxy::Proxy (const size_t len, int* subarr):
    len_ (len),
    subarr_ (subarr)
    {}
        
int& Proxy::operator[] (const size_t index)
{
    if (index >= len_) throw std::out_of_range("");
    return subarr_ [index];
}

const int& Proxy::operator[] (const size_t index) const
{
    if (index >= len_) throw std::out_of_range("");
    return subarr_ [index];
}

bool Matrix::operator == (const Matrix& right) const
{
    if (this == &right) return true;

    if ((right.cols_ != cols_) || (right.rows_ != rows_)) return false;

    for (int i = 0; i < rows_; i++)
    {
        for (int j = 0; j < cols_; j++)
        {
            if (data_[i][j] != right [i][j]) return false;
        }
    }
    return true;
}
bool Matrix::operator != (const Matrix& right) const
{
    return !(*this == right);
}

Matrix& Matrix::operator *= (const int num)
{
    for(int i = 0; i < rows_; i++)
    {
		for(int j = 0; j < cols_; j++)
            {
			data_[i][j] *= num;
            }
    }
    return *this;
}

Proxy Matrix::operator[] (const size_t index)
{
    if (index >= rows_) throw std::out_of_range("");
    return Proxy (cols_, data_ [index]);
}

const Proxy Matrix::operator[] (const size_t index) const
{
    if (index >= rows_) throw std::out_of_range("");
    return Proxy (cols_, data_ [index]);
}
