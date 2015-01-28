/**
 * Contains esrlabs::estd::vector and esrlabs::estd::declare::vector.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_VECTOR_H
#define ESTD_VECTOR_H

#include <algorithm>
#include <iterator>
#include <new>
#include <cstring>
#include <estd/nullptr.h>
#include <estd/assert.h>
#include <estd/type_traits.h>
#include <estd/constructor.h>

namespace esrlabs {
namespace estd {

    /**
     * A fixed-sized STL like vector.
     *
     * \tparam  T   Type of values of this vector.
     *
     * \section deque_example Usage example
     * \code{.cpp}
     * void addItemsToVector(esrlabs::estd::vector<int>& d)
     * {
     *     for(int i = 0; i < 10; ++i)
     *     {
     *         d.push_back(i);
     *     }
     * }
     *
     * void processVector(const esrlabs::estd::vector<int>& d)
     * {
     *     for(auto i = d.begin(); i ! = d.end(); ++i)
     *     {
     *         int item = *i;
     *         // do something with item
     *     }
     * }
     * \endcode
     *
     * This container supports adding objects of type T that do not have
     * a copy constructor or default constructor. Use the emplace methods
     * to create an instance of T directly into the vector.
     *
     * \section vector_emplace_example Emplace example
     * \code{.cpp}
     * void addEmplaceObject(esrlabs::estd::vector<ComplexObject>& d)
     * {
     *     // construct an instance of ComplexObject directly in the vector.
     *     // Calls the constructor: ComplexObject(1, 2, 3);
     *     d.emplace_back().construct(1, 2, 3);
     * }\endcode
     *
     * \see esrlabs::estd::declare::vector
     * \see esrlabs::estd::constructor
     */
    template<class T>
    class vector
    {
    public:
        /** The template parameter T */
        typedef T              value_type;
        /** A reference to the template parameter T */
        typedef T&             reference;
        /** A const reference to the template parameter T */
        typedef const T&       const_reference;
        /** A pointer to the template parameter T */
        typedef T*             pointer;
        /** A const pointer to the template parameter T */
        typedef const T*       const_pointer;
        /** An unsigned integral type for the size */
        typedef std::size_t    size_type;
        /** A signed integral type */
        typedef std::ptrdiff_t difference_type;
        /** A random access iterator */
        typedef pointer        iterator;
        /** A const random access iterator */
        typedef const_pointer  const_iterator;
        /** A random access reverse iterator */
        typedef std::reverse_iterator<iterator> reverse_iterator;
        /** A const random access reverse iterator */
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

        /**
         * A simple destructor. This destructor does not call the contained
         * object destructors. The derived class vector will call the destructors
         * on any objects in the vector.
         */
        ~vector();

        /**
         * An assignment operator. Copies values from other to this. Replacing all
         * values in this vector.
         *
         * \param other The other vector to copy.
         * \return A reference to this.
         */
        vector<T>& operator=(const vector<T>& other);

        /**
         * Replaces any element currently in this container and fills it with n
         * elements which all are initialized with a copy of value. Existing
         * elements are removed.
         *
         * \param n The number of elements to add
         * \param value The value to copy into this container.
         * \complexity  Linear in the number of elements added.
         *
         * \note
         * If n > max_size(), only max_size() elements will be added.
         */
        void assign(size_type n, const_reference value);

        /**
         * Replaces any element currently in this container and fills it with the
         * elements in [first, last).
         *
         * \param first The beginning iterator.
         * \param last The ending iterator.
         * \complexity  Linear in the number of elements added.
         *
         * \note
         * At most max_size() elements will be added.
         */
        template<class InputIterator>
        typename enable_if<!is_integral<InputIterator>::value, void>::type
        assign(
            InputIterator first,
            InputIterator last);

        /**
         * Returns current size of this vector.
         *
         * \complexity Constant
         */
        size_type size() const;

        /**
         * Returns maximum number of elements this vector can hold.
         *
         * \complexity Constant
         */
        size_type max_size() const;

        /**
         *  Returns whether this vector is empty or not.
         *
         *  \return
         *  - true if size() == 0
         *  - false otherwise
         *  \complexity Constant
         */
        bool empty() const;

        /**
         *  Returns true if the vector is full.
         *
         *  \return
         *  - true if size() == max_size()
         *  - false otherwise
         *  \complexity Constant
         */
        bool full() const;

        /**
         * Returns a reference to the element at position index in this vector.
         *
         * \param index An index into this vector.
         * \return A reference to the requested element.
         * \note
         * No bounds checking is done.
         */
        reference operator[](size_type index);

        /**
         * Returns a reference to the element at position index in this vector.
         *
         * \param index An index into this vector.
         * \return A const reference to the requested element.
         * \note
         * No bounds checking is done.
         */
        const_reference operator[](size_type index) const;

        /**
         * Returns a reference to the element at position index in this vector.
         *
         * \param index An index into this vector.
         * \return A reference to the requested element.
         * \assert{index < size()}
         */
        reference at(size_type index);

        /**
         * Returns a const reference to the element at position index in this vector.
         *
         * \param index An index into this vector.
         * \return A const reference to the requested element.
         * \assert{index < size()}
         */
        const_reference at(size_type index) const;

        /**
         * Returns a reference to the first element of this vector.
         *
         * \return A reference to the first element in the vector.
         * \assert{!empty()}
         * \complexity  Constant.
         */
        reference front();

        /**
         * Returns a const reference to the first element of this vector.
         *
         * \return A const reference to the first element in the vector.
         * \assert{!empty()}
         * \complexity  Constant.
         */
        const_reference front() const;

        /**
         * Returns a reference to the last element of this vector.
         *
         * \return A reference to the last element
         * \assert{!empty()}
         * \complexity  Constant.
         */
        reference back();

        /**
         * Returns a const reference to the last element of this vector.
         *
         * \return A const reference to the last element
         * \assert{!empty()}
         * \complexity  Constant.
         */
        const_reference back() const;

        /**
         * Default constructs an element at the end of this vector and
         * returns a reference to it increasing this vector's size by one.
         *
         * \return A reference to the newly created object.
         * \assert{!full()}
         */
        reference push_back();

        /**
         * Copy constructs an element at the end of this vector from a
         * given value increasing this vector's size by one.
         *
         * \param value The value to copy into this vector.
         * \assert{!full()}
         */
        void push_back(const_reference value);

        /**
         * Returns a constructor object to the memory allocated at the end
         * of this vector increasing this vectors size by one.
         *
         * \return A constructor object that can be used to initialize an object.
         * \assert{!full()}
         */
        constructor<T> emplace_back();

        /**
         * Returns a constructor object to the memory allocated at the position
         * indicated by the 'position' iterator. Elements are shifted to make
         * room for the new object.
         *
         * \param position An iterator to where the new object should be constructed.
         * \return A constructor object that can be used to initialize an object.
         * \assert{!full()}
         */
        constructor<T> emplace(const_iterator position);

        /**
         *  Removes last element and destroys it.
         */
        void pop_back();

        /**
         *  Inserts given value into the vector before the specified iterator.
         */
        iterator insert(const_iterator position, const_reference value);

        /**
         *  Inserts n copies of given value into the vector before the specified iterator.
         */
        void insert(const_iterator position, size_type n, const_reference value);

        /**
         *  Inserts copies of the elements in the range [first,last) at position.
         */
        template<class InputIterator>
        typename enable_if
        <   !is_integral<InputIterator>::value
        ,   iterator>::type
        insert (const_iterator position, InputIterator first, InputIterator last);

        /**
         *  Removes element at given position and destroys it.
         *  Returns iterator pointing to the next element or end().
         */
        iterator erase(const_iterator position);

        /**
         *  Removes a range [first, last) of elements destroying all of them.
         *  Returns iterator pointing to the next element or end().
         */
        iterator erase(const_iterator first, const_iterator last);

        /**
         *  Clears the vector. All elements will be destroyed.
         */
        void clear();

        /** Returns an iterator to the beginning */
        iterator begin();

        /** Returns a const iterator to the beginning */
        const_iterator begin() const;

        /** Returns a const iterator to the beginning */
        const_iterator cbegin() const;

        /** Returns an iterator to the end */
        iterator end();

        /** Returns a const iterator to the end */
        const_iterator end() const;

        /** Returns a const iterator to the end */
        const_iterator cend() const;

        /**
         * Returns a reverse iterator pointing to the last element in the vector
         * (i.e., its reverse beginning). Reverse iterators iterate backwards.
         */
        reverse_iterator rbegin();

        /**
         * Returns a const reverse iterator pointing to the last element in the vector
         * (i.e., its reverse beginning). Reverse iterators iterate backwards.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Returns a const reverse iterator pointing to the last element in the vector
         * (i.e., its reverse beginning). Reverse iterators iterate backwards.
         */
        const_reverse_iterator crbegin() const;

        /**
         * Returns a reverse iterator pointing to the first element in the vector
         * (i.e., its reverse end). Reverse iterators iterate backwards.
         */
        reverse_iterator rend();

        /**
         * Returns a const reverse iterator pointing to the first element in the vector
         * (i.e., its reverse end). Reverse iterators iterate backwards.
         */
        const_reverse_iterator rend() const;

        /**
         * Returns a const reverse iterator pointing to the first element in the vector
         * (i.e., its reverse end). Reverse iterators iterate backwards.
         */
        const_reverse_iterator crend() const;

        /**
         * Swaps this vector with another given vector.
         */
        void swap(vector& other);

    protected:

        /**
         * Constructor to initialize this vector with the actual data to work with.
         * Used by the declare class.
         *
         * \param data The actual data for this vector
         * \param size The size of the data array
         */
        vector(uint8_t data[], size_type size);

    private:

        // private and not defined
        vector(const vector<T>& other);

        uint8_t* _data;
        size_type _max_size;
        size_type _size;

        template<class InputIterator>
        void range_insert(
            const_iterator position,
            InputIterator first,
            InputIterator last,
            std::input_iterator_tag);

        template<class ForwardIterator>
        void range_insert(
            const_iterator position,
            ForwardIterator first,
            ForwardIterator last,
            std::forward_iterator_tag);
    };

    /**
     * Swaps to vectors.
     */
    template <class T>
    void
    swap(vector<T>& x, vector<T>& y);

    /**
     * Compares two vectors and returns true if they are identical.
     *
     * Requires T to have operator== defined.
     *
     * \param lhs The left-hand side of the equality.
     * \param rhs The right-hand side of the equality.
     * \return
     * - true if the vectoirs are identical
     * - false otherwise.
     */
    template<class T>
    bool
    operator==(const vector<T>& lhs, const vector<T>& rhs);

    /**
     * Compares two vectors and returns true if they are not identical.
     *
     * Requires T to have operator== defined.
     *
     * \param lhs The left-hand side of the equality.
     * \param rhs The right-hand side of the equality.
     * \return
     * - true if the vectors are not identical
     * - false otherwise.
     */
    template<class T>
    bool
    operator!=(const vector<T>& lhs, const vector<T>& rhs);

    /**
     * Compares two vectors and returns true if all elements
     * in the left-hand side are less than the elements in the
     * right hand side.
     *
     * Requires T to have operator< defined.
     *
     * \param lhs The left-hand side of the comparison.
     * \param rhs The right-hand side of the comparison.
     * \return
     * - true if the left-hand side is less than the right-hand side.
     * - false otherwise.
     */
    template<class T>
    bool
    operator<(const vector<T>& lhs, const vector<T>& rhs);

    /**
     * Compares two vectors and returns true if all elements
     * in the left-hand side are greater than the elements in the
     * right hand side.
     *
     * Requires T to have operator< defined.
     *
     * \param lhs The left-hand side of the comparison.
     * \param rhs The right-hand side of the comparison.
     * \return
     * - true if the left-hand side is greater than the right-hand side.
     * - false otherwise.
     */
    template<class T>
    bool
    operator>(const vector<T>& lhs, const vector<T>& rhs);

    /**
     * Compares two vectors and returns true if all elements
     * in the left-hand side are greater than or equal to the
     * elements in the right hand side.
     *
     * Requires T to have operator< defined.
     *
     * \param lhs The left-hand side of the comparison.
     * \param rhs The right-hand side of the comparison.
     * \return
     * - true if the left-hand side is greater than or equal to the right-hand side.
     * - false otherwise.
     */
    template<class T>
    bool
    operator>=(const vector<T>& lhs, const vector<T>& rhs);

    /**
     * Compares two vectors and returns true if all elements
     * in the left-hand side are less than or equal to the
     * elements in the right hand side.
     *
     * Requires T to have operator< defined.
     *
     * \param lhs The left-hand side of the comparison.
     * \param rhs The right-hand side of the comparison.
     * \return
     * - true if the left-hand side is less than or equal to the right-hand side.
     * - false otherwise.
     */
    template<class T>
    bool
    operator<=(const vector<T>& lhs, const vector<T>& rhs);

    /*
     * namespace to declare a vector
     */
    namespace declare
    {

        /**
         * STL like vector with static size.
         * \tparam  T   Type of values of this vector.
         * \tparam  N   Maximum number of values in this vector.
         */
        template<class T, std::size_t N>
        class vector
        :   public ::esrlabs::estd::vector<T>
        {
        public:
            typedef ::esrlabs::estd::vector<T> base;
            typedef ::esrlabs::estd::declare::vector<T, N> this_type;

            /** The template parameter T */
            typedef typename base::value_type      value_type;
            /** A reference to the template parameter T */
            typedef typename base::reference       reference;
            /** A const reference to the template parameter T */
            typedef typename base::const_reference const_reference;
            /** A pointer to the template parameter T */
            typedef typename base::pointer         pointer;
            /** A const pointer to the template parameter T */
            typedef typename base::const_pointer   const_pointer;
            /** An unsigned integral type for the size */
            typedef typename base::size_type       size_type;
            /** A signed integral type */
            typedef typename base::difference_type difference_type;
            /** A random access iterator */
            typedef typename base::iterator        iterator;
            /** A const random access iterator */
            typedef typename base::const_iterator  const_iterator;
            /** A random access reverse iterator */
            typedef typename base::reverse_iterator  reverse_iterator;
            /** A const random access reverse iterator */
            typedef typename base::const_reverse_iterator  const_reverse_iterator;

            /**
             * Constructs an empty vector.
             */
            vector();

            /**
             * Constructs a vector with n elements initialized to a given value v.
             */
            vector(size_type n, const_reference value = value_type());

            /**
             * Copies the values of the other vector into this vector.
             */
            vector(const base& other);

            /**
             * Copies the values of the other vector into this vector.
             */
            vector(const this_type& other);

            /**
             * Calls the destructor on all contained objects.
             */
            ~vector();

            /**
             * Copies the values of the other vector into this vector.
             */
            vector& operator=(const base& other);

            /**
             * Copies the values of the other vector into this vector.
             */
            vector& operator=(const this_type& other);

        private:
            uint8_t _data[sizeof(T) * N];
        };

    } /* namespace declare */

// unsupported vector<vector<T> >
// but we support vector<declare::vector<T, S> >
template<class T, template<class> class C>
class vector<C<T> >;

template <class T>inline
void swap(vector<T>& x, vector<T>& y)
{
    x.swap(y);
}

template<class T>inline
bool
operator==(const vector<T>& x, const vector<T>& y)
{
    return (x.size() == y.size())
            && std::equal(x.begin(), x.end(), y.begin());
}

template<class T>inline
bool
operator!=(const vector<T>& x, const vector<T>& y)
{
    return !(x == y);
}

template<class T>inline
bool
operator<(const vector<T>& x, const vector<T>& y)
{
    return (x.size() == y.size())
            && std::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template<class T>inline
bool
operator>(const vector<T>& x, const vector<T>& y)
{
    return (y < x);
}

template<class T>inline
bool
operator>=(const vector<T>& x, const vector<T>& y)
{
    return !(y > x);
}

template<class T>inline
bool
operator<=(const vector<T>& x, const vector<T>& y)
{
    return !(x > y);
}

/*
 *
 * Implementation of vector
 *
 */

template<class T>
vector<T>::vector(uint8_t data[], size_type size)
:   _data(data)
,   _max_size(size / sizeof(T))
,   _size(0)
{}

template<class T>
vector<T>::~vector()
{

}

template<class T>
vector<T>&
vector<T>::operator=(const vector<T>& other)
{
    // identical vector
    if(_data == other._data)
    {
        return *this;
    }

    estd_assert(_max_size >= other._size);

    if (size() >= other.size())
    {
        std::copy(other.cbegin(), other.cend(), begin());
        erase(begin() + other.size(), end());
    }
    else
    {
        std::copy(other.cbegin(), other.cbegin() + size(), begin());
        insert(begin() + size(), other.cbegin() + size(), other.cend());
    }

    return *this;
}

template<class T>inline
void
vector<T>::assign(size_type n, const_reference value)
{
    clear();
    n = std::min(n, max_size());
    while (n > 0)
    {
        emplace_back().construct(value);
        --n;
    }
}

template<class T>
template<class InputIterator>inline
typename enable_if
<   !is_integral<InputIterator>::value
,   void
>::type
vector<T>::assign(InputIterator first, InputIterator last)
{
    clear();
    while (!full() && (first != last))
    {
        emplace_back().construct(*first);
        ++first;
    }
}

template<class T>inline
typename vector<T>::iterator
vector<T>::begin()
{
    return reinterpret_cast<pointer>(&_data[0]);
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::begin() const
{
    return reinterpret_cast<const_pointer>(&_data[0]);
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::cbegin() const
{
    return begin();
}

template<class T>inline
typename vector<T>::iterator
vector<T>::end()
{
    return reinterpret_cast<pointer>(&_data[_size * sizeof(T)]);
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::end() const
{
    return reinterpret_cast<const_pointer>(&_data[_size * sizeof(T)]);
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::cend() const
{
    return end();
}

template<class T>inline
typename vector<T>::reverse_iterator
vector<T>::rbegin()
{
    return reverse_iterator(end());
}

template<class T>inline
typename vector<T>::const_reverse_iterator
vector<T>::rbegin() const
{
    return const_reverse_iterator(end());
}

template<class T>inline
typename vector<T>::const_reverse_iterator
vector<T>::crbegin() const
{
    return rbegin();
}

template<class T>inline
typename vector<T>::reverse_iterator
vector<T>::rend()
{
    return reverse_iterator(begin());
}

template<class T>inline
typename vector<T>::const_reverse_iterator
vector<T>::rend() const
{
    return const_reverse_iterator(begin());
}

template<class T>inline
typename vector<T>::const_reverse_iterator
vector<T>::crend() const
{
    return rend();
}

template<class T>inline
typename vector<T>::size_type
vector<T>::size() const
{
    return _size;
}

template<class T>inline
typename vector<T>::size_type
vector<T>::max_size() const
{
    return _max_size;
}

template<class T>inline
bool
vector<T>::empty() const
{
    return (0 == _size);
}

template<class T>inline
bool
vector<T>::full() const
{
    return (_size == _max_size);
}

template<class T>inline
typename vector<T>::reference
vector<T>::operator[](size_type index)
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->operator[](index));
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::operator[](size_type index) const
{
    return *reinterpret_cast<const_pointer>(&_data[index * sizeof(T)]);
}

template<class T>inline
typename vector<T>::reference
vector<T>::at(size_type index)
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->at(index));
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::at(size_type index) const
{
    estd_assert(index < size());
    return operator[](index);
}

template<class T>inline
typename vector<T>::reference
vector<T>::front()
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->front());
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::front() const
{
    estd_assert(size() > 0);
    return *reinterpret_cast<const_pointer>(_data);
}

template<class T>inline
typename vector<T>::reference
vector<T>::back()
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->back());
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::back() const
{
    estd_assert(size() > 0);
    return *reinterpret_cast<const_pointer>(&_data[sizeof(T) * (_size - 1)]);
}

template<class T>inline
typename vector<T>::reference
vector<T>::push_back()
{
    estd_assert(!full());
    return *new(&_data[sizeof(T) * _size++])T();
}

template<class T>inline
void
vector<T>::push_back(const_reference value)
{
    estd_assert(!full());
    (void)*new(&_data[sizeof(T) * _size++])T(value);
}

template<class T>inline
constructor<T>
vector<T>::emplace_back()
{
    estd_assert(!full());
    return constructor<T>(&_data[sizeof(T) * _size++]);
}

template<class T>inline
constructor<T>
vector<T>::emplace(const_iterator position)
{
    estd_assert(!full());
    iterator dst = const_cast<iterator>(position);
    memmove(dst + 1, position, (sizeof(T) * (cend() - position)));
    ++_size;
    return constructor<T>(reinterpret_cast<uint8_t*>(dst));
}

template<class T>inline
void
vector<T>::pop_back()
{
    estd_assert(size() > 0);
    reinterpret_cast<T*>(&_data[sizeof(T) * _size--])->~T();
}

template<class T>inline
typename vector<T>::iterator
vector<T>::insert(const_iterator position, const_reference value)
{
    estd_assert(size() < max_size());
    iterator dst = const_cast<iterator>(position);
    memmove(dst + 1, position, (sizeof(T) * (cend() - position)));
    (void)new(dst)value_type(value);
    ++_size;
    return dst;
}

template<class T>inline
void
vector<T>::insert(const_iterator position, size_type n, const_reference value)
{
    estd_assert((size() + n) <= max_size());
    iterator dst = const_cast<iterator>(position);
    memmove(dst + n, position, (sizeof(T) * (cend() - position)));
    for (size_t i = 0; i < n; ++i)
    {
        (void)new(dst++)value_type(value);
    }
    _size += n;
}

template<class T>
template<class InputIterator>
typename enable_if
<   !is_integral<InputIterator>::value
,   typename vector<T>::iterator
>::type
vector<T>::insert(const_iterator position, InputIterator first, InputIterator last)
{
    iterator start = const_cast<iterator>(position);

    typedef typename std::iterator_traits<InputIterator>::iterator_category IteratorCategory;
    range_insert(position, first, last, IteratorCategory());

    return start;
}

template<class T>inline
typename vector<T>::iterator
vector<T>::erase(const_iterator position)
{
    iterator item = iterator(position);
    if (position == cend())
    {
        return item;
    }
    estd_assert(size() > 0);
    item->~T();

    if (position + 1 != cend())
    {
        memmove(item, position + 1, sizeof(T) * (cend() - position - 1));
    }
    --_size;
    return item;
}

template<class T>inline
typename vector<T>::iterator
vector<T>::erase(const_iterator first, const_iterator last)
{
    estd_assert(last <= cend());
    if (last < first) { return iterator(last); } //should this be an assert?
    for (iterator i = iterator(first), l = iterator(last); i != l; ++i)
    {
        i->~T();
    }
    memmove(iterator(first), iterator(last), (sizeof(T) * (cend() - last)));
    _size -= (last - first);
    return iterator(first);
}

template<class T>inline
void
vector<T>::clear()
{
    for (size_t i = 0; i < _size; ++i)
    {
        reinterpret_cast<T*>(&_data[sizeof(T) * i])->~T();
    }
    _size = 0;
}

template<class T>inline
void
vector<T>::swap(vector<T>& other)
{
    std::swap(_data, other._data);
    std::swap(_max_size, other._max_size);
    std::swap(_size, other._size);
}

template<class T>
template<class InputIterator>inline
void
vector<T>::range_insert(
    const_iterator position,
    InputIterator first,
    InputIterator last,
    std::input_iterator_tag)
{
    while (!full() && (first != last))
    {
        insert(position, *first);
        ++position;
        ++first;
    }
}

template<class T>
template<class ForwardIterator>inline
void
vector<T>::range_insert(
    const_iterator position,
    ForwardIterator first,
    ForwardIterator last,
    std::forward_iterator_tag)
{
    while (!full() && (first != last))
    {
        insert(position, *first);
        ++position;
        ++first;
    }
}

namespace declare
{

    template<class T, std::size_t N>
    vector<T, N>::vector()
    :   ::esrlabs::estd::vector<T>(_data, sizeof(_data))
    ,   _data()
    {}

    template<class T, std::size_t N>
    vector<T, N>::vector(size_type n, const_reference value)
    :   ::esrlabs::estd::vector<T>(_data, sizeof(_data))
    ,   _data()
    {
        base::assign(std::min(n, N), value);
    }

    template<class T, size_t N>
    vector<T, N>::vector(const estd::vector<T>& other)
    :   ::esrlabs::estd::vector<T>(_data, sizeof(_data))
    ,   _data()
    {
        base::operator=(other);
    }

    template<class T, size_t N>
    vector<T, N>::vector(const estd::declare::vector<T, N>& other)
    :   ::esrlabs::estd::vector<T>(_data, sizeof(_data))
    ,   _data()
    {
        base::operator=(other);
    }

    template<class T, size_t N>
    vector<T, N>::~vector()
    {
        base::clear();
    }

    template<class T, size_t N>
    vector<T, N>&
    vector<T, N>::operator=(const esrlabs::estd::vector<T>& other)
    {
        base::operator=(other);
        return *this;
    }

    template<class T, size_t N>
    vector<T, N>&
    vector<T, N>::operator=(const esrlabs::estd::declare::vector<T, N>& other)
    {
        base::operator=(other);
        return *this;
    }

} /* namespace declare */

} /* namespace estd */

} /* namespace esrlabs */

#endif
