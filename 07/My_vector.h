#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <limits>

template <typename T>
class my_allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using size_type = size_t;

    pointer allocate(size_type count)
    {
        if (count == 0) throw std::bad_alloc ();
        if (count > max_size()) throw std::bad_alloc ();
        pointer ptr = (pointer)(:: operator new (sizeof (value_type)*count));
        if (ptr == nullptr) throw std::bad_alloc ();
        return ptr;
    }

    void deallocate(pointer ptr, size_type count)
    {
        :: operator delete (ptr);
    }

    void construct (pointer ptr, const value_type& val)
    {
        new (ptr) value_type (val);
    }

    void destruct (pointer ptr)
    {
        ptr->~value_type();
    }

    size_type max_size() const noexcept
    {
        return std::numeric_limits<size_type>::max()/ sizeof(value_type);
    }
};

template <typename T>
class my_iterator: public std::iterator<std::random_access_iterator_tag, T>
{
    private:
        T* ptr_;

    public:
        using iterator = my_iterator<T>;
        using difference_type = ptrdiff_t;
        using value_type = T;
        using reference = T&;
        using pointer = T*;

        explicit my_iterator (pointer ptr):
            ptr_(ptr)
            {}

        my_iterator(const iterator& other):
            ptr_(other.ptr_)
            {}

        bool operator==(const iterator& other) const
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const iterator& other) const
        {
            return !(*this == other);
        }

        bool operator<(const iterator& other) const
        {
            return ptr_ < other.ptr_;
        }

        bool operator>(const iterator& other) const
        {
            return ptr_ > other.ptr_;
        }

        bool operator>=(const iterator& other) const
        {
            return ptr_ >= other.ptr_;
        }

        bool operator<=(const iterator& other) const
        {
            return ptr_ <= other.ptr_;
        }

        reference operator*() const
        {
            return *ptr_;
        }

        iterator& operator++()
        {
            ++ptr_;
            return *this;
        }

        iterator& operator--()
        {
            --ptr_;
            return *this;
        }

        iterator& operator+=(difference_type count)
        {
            ptr_ += count;
            return *this;
        }

        iterator& operator-=(difference_type count)
        {
            ptr_ -= count;
            return *this;
        }

        iterator operator+(difference_type count)
        {
            iterator tmp(ptr_ + count);
            return tmp;
        }

        iterator operator-(difference_type count)
        {
            iterator tmp(ptr_ - count);
            return tmp;
        }

        iterator operator+(const iterator& other)
        {
          iterator tmp(ptr_ + other.ptr_);
          return tmp;
        }

        iterator operator-(const iterator& other)
        {
          iterator tmp(ptr_ - other.ptr_);
          return tmp;
        }

        reference operator[](int count) const
        {
            return ptr_[count];
        }
};

template<class T,
    class Alloc = my_allocator<T>>
class my_vector
{
    public:
        using size_type = size_t;
        using value_type = T;
        using pointer = T*;
        using reference = T&;
        using const_reference = const T&;
    	using allocator_type = Alloc;
        using iterator = my_iterator<T>;
        using reverse_iterator = std::reverse_iterator<iterator>;

        my_vector ():
            size_ (0),
            capacity_ (0),
            data_ (nullptr)
            {}
        explicit my_vector(size_type count):
            size_ (0),
            capacity_ (count),
            data_ (alloc_.allocate(count))
            {}

        my_vector(size_type count, const value_type& defaultValue):
            size_ (count),
            capacity_ (count),
            data_ (alloc_.allocate(count))
            {
            for (size_type i = 0; i < count; i++)
                alloc_.construct(data_ + i, defaultValue);
            }

        ~my_vector ()
        {
            for (size_type i = 0; i < size_; i++)
                alloc_.destruct (data_ + i);
            alloc_.deallocate (data_, capacity_);
        }

        iterator begin() noexcept
        {
            return iterator (data_);
        }

        iterator end() noexcept
        {
            return iterator (data_ + size_);
        }

        reverse_iterator rbegin() noexcept
        {
            return reverse_iterator (end());
        }

        reverse_iterator rend() noexcept
        {
            return reverse_iterator (begin());
        }

        void push_back(value_type&& value)
        {
            if (capacity_ == 0) reserve (1);
            else if (size_ == capacity_) reserve (2*capacity_);
            data_[size_] = std::move (value);
            size_++;
        }

        void push_back(const value_type& value)
        {
            if (capacity_ == 0) reserve (1);
            else if (size_ == capacity_) reserve (2*capacity_);
            data_[size_] = value;
            size_++;
        }

        reference operator[] (size_type ind)
        {
            return data_ [ind];
        }

        const reference operator[] (size_type ind) const
        {
            return data_ [ind];
        }

        value_type pop_back ()
        {
            if (size_ == 0) throw std::runtime_error ("Nothing to pop");
            value_type ret = data_ [size_ - 1];
            size_--;

            return ret;
        }

        void reserve(size_type count)
        {
            if (count > capacity_)
            {
                pointer tmp = alloc_.allocate (count);

                for (size_type i = 0; i < capacity_; i++)
                {
                    alloc_.construct(tmp + i, data_[i]);
                }

                for (size_type i = 0; i < capacity_; i++)
                {
                    alloc_.destruct(data_ + i);
                }

                alloc_.deallocate(data_, capacity_);
                data_ = tmp;
                capacity_ = count;
            }
        }

        size_type capacity() const noexcept
        {
            return capacity_;
        }

        void resize(size_type newSize)
        {
            if (newSize > size_)
            {
                if (capacity_ < newSize) reserve (newSize);
                for (size_type i = size_; i < newSize; i++)
                {
                    alloc_.construct(data_+i, data_[0]);
                }
            }

        else
        {
            for (size_type i = newSize; i < size_; i++)
            {
                alloc_.destruct(data_ + i);
            }
        }
        capacity_  = newSize;
        size_ = newSize;
        }

        bool empty () const noexcept
        {
            return (size_ == 0);
        }

        size_type size () const noexcept
        {
            return size_;
        }

        void clear() noexcept
        {
            for (size_type i = 0; i < size_; i++)
                alloc_.destruct(data_ + i);
            size_ = 0;
        }

    private:
        size_type size_;
        size_type capacity_;
        pointer data_;
        allocator_type alloc_;
};



#endif //MY_VECTOR_H
