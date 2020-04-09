#ifndef BIGINT_H
#define BIGINT_H

class BigInt
{
    private:
        long long len_;//unsigned?
        bool minus_;
        char* data_;

    public:
        BigInt ();
        BigInt (const int number);
        BigInt (const char* number);
        BigInt (long long len, bool minus);
        BigInt (const BigInt &source);

        ~BigInt ();

        BigInt abs () const;
        BigInt& operator= (const BigInt& source);
        BigInt operator- () const;
        bool operator<  (const BigInt& right) const;
        bool operator>  (const BigInt& right) const;
        bool operator>= (const BigInt& right) const;
        bool operator<= (const BigInt& right) const;
        bool operator== (const BigInt& right) const;
        bool operator!= (const BigInt& right) const;


        friend BigInt add (const BigInt& left, const BigInt& right);//to private later
        friend BigInt sub (const BigInt& left, const BigInt& right);

        friend BigInt operator+ (const BigInt& left, const BigInt& right);
        friend BigInt operator- (const BigInt& left, const BigInt& right);
        friend std::ostream& operator<<(std::ostream& os, const BigInt& num);

};


#endif //BIGINT_H
