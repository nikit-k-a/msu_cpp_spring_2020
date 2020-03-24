#ifndef MATRIX_H
#define MATRIX_H

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

        size_t getRows () { return cols_; } const
        size_t getCols () { return rows_; } const

        bool operator == (const Matrix& right) const;
        bool operator != (const Matrix& right) const;

        Matrix& operator *= (const int num) const;

        class Proxy
        {
            public:
                Proxy (const size_t len, int* subarr):
                    len_ (len),
                    subarr_ (subarr)
                    {}

                int& operator[] (const size_t index)
                {
                    return subarr_ [index];
                }

                const int& operator[] (const size_t index) const
                {
                    return subarr_ [index];
                }

            private:
                const int len_;
                int* subarr_;
        };

    Proxy operator[] (const size_t index)
    {
        return Proxy (cols_, data_ [index]);
    }

    const Proxy operator[] (const size_t index) const
    {
        return Proxy (cols_, data_ [index]);
    }
};


#endif //CALLBACK_H
