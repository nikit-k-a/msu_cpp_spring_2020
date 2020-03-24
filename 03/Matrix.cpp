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

bool Matrix::operator == (Matrix& right) const
{
    if (this == &right) return true;

    if (right.cols_ != cols_ or A.rows_ != rows_) return false;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (data_[i][j] != right [i][j]) return false;
        }
    }
    return true;
}

bool Matrix::operator != (Matrix& right) const
{
    return !(*this == A);
}

Matrix& Matrix::operator *= (const int num) const
{
    for(int i = 0; i < rows; i++)
    {
		for(int j = 0; j < columns; j++)
            {
			matrix[i][j] *= num;
            }
    }
    return *this;
}
