/**
 * Contains esrlabs::estd::vector.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_VECTOR_H
#define ESTD_VECTOR_H

#include <iterator>

#include <estd/uncopyable.h>
#include <estd/nullptr.h>
#include <estd/assert.h>

namespace esrlabs {
namespace estd {

/**
 * Base class for statically sized STL like vector.
 * \author  daniel.schick@esrlabs.com
 * \tparam  T   Type of values of this vector.
 */
template<class T>
class vector
{
    UNCOPYABLE(vector);
public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    /**
     *  Fill a vector with n copies of the given value val.
     */
    void
    assign(size_type n, const_reference val);

    /**
     *  Fill a vector with copies of the elements in the range [first,last).
     */
    template<class InputIterator>
    void
    assign(InputIterator first, InputIterator last);

    iterator
    begin();

    const_iterator
    begin() const;

    const_iterator
    cbegin() const;

    iterator
    end();

    const_iterator
    end() const;

    const_iterator
    cend() const;

    reverse_iterator
    rbegin();

    const_reverse_iterator
    rbegin() const;

    const_reverse_iterator
    crbegin() const;

    reverse_iterator
    rend();

    const_reverse_iterator
    rend() const;

    const_reverse_iterator
    crend() const;

    size_type
    size() const;

    size_type
    max_size() const;

    /**
     *  Returns true if the vector is empty.
     */
    bool
    empty() const;

    /**
     *  Returns true if the vector is full.
     */
    bool
    full() const;

    /**
     * Returns a reference to the element at position n in this vector.
     */
    reference
    operator[](size_type n);

    /**
     * Returns a const reference to the element at position n in this vector.
     */
    const_reference
    operator[](size_type n) const;

    /**
    * Returns a reference to the element at position n in this vector.
    * \pre   n < size()
    * \throw assert(n < size())
    */
    reference
    at(size_type n);

    /**
    * Returns a const reference to the element at position n in this vector.
    * \pre   n < size()
    * \throw assert(n < size())
    */
    const_reference
    at(size_type n) const;

    /**
     * Returns a reference to the first  element in this vector.
     */
    reference
    front();

    /**
     * Returns a const reference to the first element in this vector.
     */
    const_reference
    front() const;

    /**
     * Returns a reference to the last element in this vector.
     */
    reference
    back();

    /**
     * Returns a const reference to the last element in this vector.
     */
    const_reference
    back() const;

    /**
     *  Add data to the end of the vector.
     */
    reference
    push_back();
    void
    push_back(const_reference val);

    /**
     *  Remove last element.
     */
    void
    pop_back();

    /**
     *  Insert given value into the vector before the specified iterator.
     */
    iterator
    insert(iterator position, const_reference val);

    /**
     *  Insert n copies of given value into the vector before the specified iterator.
     */
    void
    insert(iterator position, size_type n, const_reference val);

    /**
     *  Insert copies of the elements in the range [first,last) at position.
     */
    template<class InputIterator>
    void
    insert (iterator position, InputIterator first, InputIterator last);

    /**
     *  Remove element at given position.
     *  Returns iterator pointing to the next element or end().
     */
    iterator
    erase(iterator position);

    /**
     *  Remove a range [first, last) of elements.
     *  Returns iterator pointing to the next element or end().
     */
    iterator
    erase(iterator first, iterator last);

    /**
     *  Clear the vector. Does not call destructors of the contained elements.
     */
    void
    clear();

protected:
    explicit vector(value_type data[], size_type size);

private:
    value_type* _data;
    size_type _max_size;
    size_type _size;

    template<class InputIterator>
    void
    range_insert(
        iterator position,
        InputIterator first,
        InputIterator last,
        std::input_iterator_tag);

    template<class ForwardIterator>
    void
    range_insert(
        iterator position,
        ForwardIterator first,
        ForwardIterator last,
        std::forward_iterator_tag);
};

/*
 * namespace to declare a vector
 */
namespace declare
{

    /**
     * STL like vector with static size.
     * \author  daniel.schick@esrlabs.com
     * \tparam  T   Type of values of this vector.
     * \tparam  N   Maximum number of values in this vector.
     */
    template<class T, std::size_t N>
    class vector
    :   public ::esrlabs::estd::vector<T>
    {
        UNCOPYABLE(vector);
        typedef ::esrlabs::estd::vector<T> base;
    public:
        typedef typename base::value_type value_type;
        typedef typename base::const_reference const_reference;
        typedef typename base::size_type size_type;
        typedef typename base::iterator iterator;
        typedef typename base::const_iterator const_iterator;

        /**
         * Constructs an empty vector.
         */
        vector();

        /**
         * Constructs a vector with n elements initialized to a given value v.
         */
        vector(size_type n, const_reference val = value_type());
    private:
        T _data[N];
    };

} /* namespace declare */

// unsupported vector<vector<T> >
// but we support vector<declare::vector<T, S> >
template<class T, template<class> class C>
class vector<C<T> >;

/*
 * Implementation of vector
 */
template<class T>
vector<T>::vector(value_type data[], size_type size)
:   _data(data)
,   _max_size(size)
,   _size(0)
{}

template<class T>inline
void
vector<T>::assign(size_type n, const_reference val)
{
    if (n > _max_size) return;
    std::fill(begin(), begin() + n, val);
    _size = n;
}

template<class T>
template<class InputIterator>inline
void
vector<T>::assign(InputIterator first, InputIterator last)
{
    clear();
    while (!full() && (first != last))
    {
        push_back() = *first;
        ++first;
    }
}

template<class T>inline
typename vector<T>::iterator
vector<T>::begin()
{
    return &_data[0];
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::begin() const
{
    return &_data[0];
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
    return &_data[_size];
}

template<class T>inline
typename vector<T>::const_iterator
vector<T>::end() const
{
    return &_data[_size];
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
vector<T>::operator[](size_type n)
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->operator[](n));
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::operator[](size_type n) const
{
    return _data[n];
}

template<class T>inline
typename vector<T>::reference
vector<T>::at(size_type n)
{
    return const_cast<reference>(static_cast<const vector<T>*>(this)->at(n));
}

template<class T>inline
typename vector<T>::const_reference
vector<T>::at(size_type n) const
{
    estd_assert(n < size());
    return operator[](n);
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
    return _data[0];
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
    return _data[_size - 1];
}

template<class T>inline
typename vector<T>::reference
vector<T>::push_back()
{
    estd_assert(!full());
    return _data[_size++];
}

template<class T>inline
void
vector<T>::push_back(const_reference val)
{
    if (full()) return;
    push_back() = val;
}

template<class T>inline
void
vector<T>::pop_back()
{
    estd_assert(size() > 0);
    --_size;
}

template<class T>inline
typename vector<T>::iterator
vector<T>::insert(iterator position, const_reference val)
{
    estd_assert(size() < max_size());
    std::copy_backward(position, end(), end() + 1);
    *position = val;
    ++_size;
    return position;
}

template<class T>inline
void
vector<T>::insert(iterator position, size_type n, const_reference val)
{
    estd_assert((size() + n) <= max_size());
    std::copy_backward(position, end(), end() + n);
    std::fill(position, position + n, val);
    _size+= n;
}

template<class T>
template<class InputIterator>inline
void
vector<T>::insert(iterator position, InputIterator first, InputIterator last)
{
    typedef typename std::iterator_traits<InputIterator>::
        iterator_category IteratorCategory;
    range_insert(position, first, last, IteratorCategory());
}

template<class T>inline
typename vector<T>::iterator
vector<T>::erase(iterator position)
{
    estd_assert(size() > 0);
    if (position + 1 != end())
    {
        std::copy(position + 1, end(), position);
    }
    --_size;
    return position;
}

template<class T>inline
typename vector<T>::iterator
vector<T>::erase(iterator first, iterator last)
{
    difference_type d = std::distance(first, last);
    if (d < 0) d = 0;
    estd_assert(size() >= size_type(d));
    if (first != last)
    {
        if (last != end())
        {
            std::copy(last, end(), first);
        }
    }
    _size -= d;
    return first;
}

template<class T>inline
void
vector<T>::clear()
{
    _size = 0;
}

template<class T>
template<class InputIterator>inline
void
vector<T>::range_insert(
    iterator position,
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
    iterator position,
    ForwardIterator first,
    ForwardIterator last,
    std::forward_iterator_tag)
{
    difference_type d = std::distance(first, last);
    if (d <= 0) return;
    estd_assert((size() + size_type(d)) <= max_size());
    std::copy_backward(position, end(), end() + d);
    std::copy(first, last, position);
    _size += d;
}

namespace declare
{

    template<class T, std::size_t N>
    vector<T, N>::vector()
    :   ::esrlabs::estd::vector<T>(_data, N)
    ,   _data()
    {}

    template<class T, std::size_t N>
    vector<T, N>::vector(size_type n, const_reference val)
    :   ::esrlabs::estd::vector<T>(_data, N)
    ,   _data()
    {
        base::assign(std::min(n, N), val);
    }

} /* namespace declare */

} /* namespace estd */

} /* namespace esrlabs */

#endif
