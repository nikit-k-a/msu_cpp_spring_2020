#include <iostream>
#include "BigInt.h"

#include <cstring>

BigInt::BigInt ():
    len_ (0),
    minus_ (false),
    data_ (nullptr)
    {}

BigInt::BigInt (long long len, bool minus):
    len_ (len),
    minus_ (minus),
    data_ (new char [len])
    {}


BigInt::BigInt (const BigInt &source):
    len_ (source.len_),
    minus_ (source.minus_),
    data_ (new char [source.len_])
    {
        std::copy(source.data_, source.data_ + len_, data_);
    }

BigInt::BigInt (const int number):
    len_ (0),
    minus_ (false),
    data_ (nullptr)
    {
        int tmp = number;
        if (tmp < 0)
        {
            minus_ = true;
            tmp = -tmp;
        }
        len_ = std::to_string (tmp).length ();
        if (len_ < 0) len_ = 0;

        data_ = new char [len_];
        for (int i = len_ - 1; i >= 0; i--)
           {
               data_[i] = tmp % 10 + '0';
               tmp /= 10;
           }
    }

BigInt::BigInt (const char* num):
    len_ (0),
    minus_ (false),
    data_ (nullptr)
    {
        int start = 0;
        if (num [0] == '-')
        {
            minus_ = true;
            start = 1;
            len_ = std::strlen (num) - 1;
        }
        else
        {
            start = 0;
            len_ = std::strlen (num);
        }
        data_ = new char [len_ + 1];
        for (int i = start; i < len_ + start; i++)
            {
                data_ [i - start] = num [i];
            }
    }

BigInt::~BigInt ()
{
    delete [] data_;
}

BigInt& BigInt::operator= (const BigInt &source)
{
    if (this == &source)
        return *this;

    char* tmp_ptr = new char [source.len_];
    delete[] data_;
    data_ = tmp_ptr;
    len_ = source.len_;
    minus_ = source.minus_;
    std::copy(source.data_, source.data_ + len_, data_);

    return *this;
}

BigInt BigInt::operator- () const
{
    if (*this == 0)
	{
		return *this;
	}

    BigInt tmp (*this);
    tmp.minus_ = !tmp.minus_;
    return tmp;
}

BigInt BigInt::abs () const
{
    if (*this == 0)
	{
		return *this;
	}

    BigInt tmp (*this);
    tmp.minus_ = false;
    return tmp;
}

BigInt operator+ (const BigInt& left, const BigInt& right)
{
    if (left.minus_ && right.minus_)
    {
        return -add(left, right);;
    }

    if (left.minus_ && !right.minus_)
    {
        return (right - left.abs ());
    }

    if (!left.minus_ && right.minus_)
    {
        return (left - right.abs ());
    }

    else
    {
        return add(left, right);
    }
}

BigInt operator- (const BigInt& left, const BigInt& right)
{
    BigInt zero (0);
    if (left == right) return zero;
    if (!left.minus_ && right.minus_)
    {
        return add (left, right);
    }

    if (left.minus_ && !right.minus_)
    {
        return -add (left.abs(), right);
    }

    if (left.abs() > right.abs())
    {
        if (left.minus_ && right.minus_)
        {
            return -sub (right, left);
        }

        else
        {
            return sub (left, right);
        }
    }

    else
    {
        if (left.minus_ && right.minus_)
        {
            return sub (right, left);
        }

        else
        {
            return sub (left, right);
        }
    }

}

BigInt add (const BigInt& left, const BigInt& right)
{
    long long max_sz = std::max(left.len_, right.len_);
	long long min_sz = std::min(left.len_, right.len_);
	long long diff = max_sz - min_sz;

    BigInt lft (max_sz, false);
    BigInt rgt (max_sz, false);
    if (left.len_ < max_sz)
    {
        for (int i = 0; i < max_sz; i++)
        {
            if (i < diff) lft.data_[i] = '0';
            if (i >= diff) lft.data_[i] = left.data_ [i - diff];
        }
    rgt = right;
    }

    else if (right.len_ <= max_sz)
    {
        for (int i = 0; i < max_sz; i++)
        {
            if (i < diff) rgt.data_[i] = '0';
            if (i >= diff) rgt.data_[i] = right.data_ [i - diff];
        }
    lft = left;
    }
    BigInt tmp (max_sz + 1, false);
	int carry = 0;
    for (int i = max_sz - 1; i >= 0; i--)
    {
        int sum = lft.data_ [i] - '0' + rgt.data_ [i] - '0' + carry;
        tmp.data_[i] = sum%10 + '0';
        carry = sum/10;
    }

    tmp.len_ = max_sz;
	if (carry != 0)
	{
        tmp.len_++;
        for (int i = tmp.len_ - 1; i > 0; i--)
        {
            tmp.data_ [i] = tmp.data_ [i - 1];
        }
        tmp.data_[0] = carry + '0';
	}
	return tmp;
}

BigInt sub (const BigInt& left, const BigInt& right)
{
    long long max_sz = std::max(left.len_, right.len_);
    long long min_sz = std::min(left.len_, right.len_);
    long long diff = max_sz - min_sz;

    BigInt bigger (max_sz, false);
    BigInt less (max_sz, false);

    BigInt tmp (max_sz, false);
    if (left > right)
    {
        bigger = left;
        less = right;
    }

    else
    {
        bigger = right;
        less = left;
        tmp.minus_ = true;
    }

    int carry = 0;
    int index = 0;
    for (int i = less.len_ - 1; i >= 0; i--)
    {
        int sub = ((bigger.data_ [i + diff] - '0') - (less.data_ [i] - '0') - carry);
		if (sub < 0)
        {
			sub = sub+10;
			carry = 1;
        }

		else
		{
            carry = 0;
        }

		tmp.data_ [index] = (sub + '0');
        index++;
    }

	for (int i = diff - 1; i >= 0; i--)
    {
        if (bigger.data_ [i] == '0' && carry)
        {
		    tmp.data_ [index] = '9';
            index++;
			continue;
        }

		int sub = ((bigger.data_ [i] - '0') - carry);
		if (i > 0 || sub > 0)
        {
			tmp.data_ [index] = sub + '0';
            index++;
        }
		carry = 0;
    }

    tmp.len_ = index;

    for (int i = index - 1; tmp.data_ [i] == '0' && i > 0; i--)
    {
        tmp.len_--;
    }

    char temp = 0;
    for (int i = 0; i < tmp.len_/2; i++)
    {
        temp = tmp.data_ [i];
        tmp.data_ [i] = tmp.data_ [tmp.len_ - i - 1];
        tmp.data_ [tmp.len_ - i - 1] = temp;
    }
    return tmp;
}

bool BigInt::operator< (const BigInt& right) const
{
    if (minus_ != right.minus_)
        return minus_;

    if (len_ != right.len_)
        {
            if (len_ < right.len_) return true;
            else return false;
        }

    for (int i = 0; i < len_; i++)
    {
        if (data_ [i] < right.data_ [i])
        {
            return true;
        }
        if (data_ [i] > right.data_ [i])
        {
            return false;
        }
    }
    return false;
}

bool BigInt::operator> (const BigInt& right) const
{
    return (!(*this < right) && !(*this == right));
}

bool BigInt::operator>= (const BigInt& right) const
{
    return !(*this < right);
}

bool BigInt::operator<= (const BigInt& right) const
{
    return !(*this > right);
}

bool BigInt::operator== (const BigInt& right) const
{
    if (this == &right) return true;
    if (len_ != right.len_) return false;
    if (minus_ != right.minus_) return false;
    if (len_ == 0 && right.len_ == 0) return true;

    for (int i = 0; i < len_; i++)
    {
        if (data_ [i] != right.data_ [i]) return false;
    }

    return true;
}
bool BigInt::operator!= (const BigInt& right) const
{
    return (!(*this == right));
}
std::ostream& operator<<(std::ostream& os, const BigInt& num)
{
    if (num.minus_) os << '-';
    for (size_t i = 0; i < num.len_; i++)
        os << num.data_ [i];

    return os;
}
