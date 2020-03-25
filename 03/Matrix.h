#ifndef MATRIX_H
#define MATRIX_H


class Proxy
{
    private:
        const size_t len_;
        int* subarr_;

    public:
        Proxy (const size_t len, int* subarr);

        int& operator[] (const size_t index);
        const int& operator[] (const size_t index) const;
};

class Matrix
{
    private:
        const size_t rows_;
        const size_t cols_;
        int** data_;

    public:
        Matrix ();
        Matrix (const size_t rows, const size_t cols);
        ~Matrix ();

        size_t getRows () const { return rows_; }
        size_t getCols () const { return cols_; }

        bool operator == (const Matrix& right) const;
        bool operator != (const Matrix& right) const;

        Matrix& operator *= (const int num);

        Proxy operator[] (const size_t index);
        const Proxy operator[] (const size_t index) const;
};

#endif //CALLBACK_H
