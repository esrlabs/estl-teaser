/**
 * Contains esrlabs::estd::constructor.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_CONSTRUCTOR_H
#define ESTD_CONSTRUCTOR_H

#include <estd/estdint.h>

namespace esrlabs {
namespace estd {

    /**
     * A template class that provides a portable way to construct
     * objects from memory that is owned by a fixed-size container.
     * This class makes it possible to add objects that do not have
     * default constructors. It is used for all of the emplace methods.
     *
     * \tparam T The type of object to construct.
     *
     * \section constructor_vector_example Vector Example
     * \code{.cpp}
     class MyClass
     {
         public:
             MyClass(int i);
     };

     void emplaceExample(esrlabs::estd::vector<MyClass>& v)
     {
         for(int i = 0; i < 10; ++i)
         {
             // call the MyClass(int) constructor
             v.emplace_back().construct(i);
         }
     }\endcode
     */
    template<class T>
    class constructor
    {
    public:
        /**
         * Initializes this constructor object with the specified
         * memory address.
         */
        constructor(uint8_t mem[]);

        /**
         * Constructs an object of type T with the default constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \return A newly created object.
         */
        T& construct();

        /**
         * Constructs an object of type T by calling the copy constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 A reference to another object of type T
         * \return A newly created object.
         */
        T& construct(const T& p1);

        /**
         * Constructs an object of type T by calling the a single
         * argument constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 The parameter to pass to the constructor.
         * \return A newly created object.
         */
        template<class P1>
        T& construct(P1 p1);

        /**
         * Constructs an object of type T by calling a
         * two argument constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 The first parameter to pass to the constructor.
         * \param p2 The second parameter to pass to the constructor.
         * \return A newly created object.
         */
        template<class P1, class P2>
        T& construct(P1 p1, P2 p2);

        /**
         * Constructs an object of type T by calling a
         * three argument constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 The first parameter to pass to the constructor.
         * \param p2 The second parameter to pass to the constructor.
         * \param p3 The third parameter to pass to the constructor.
         * \return A newly created object.
         */
        template<class P1, class P2, class P3>
        T& construct(P1 p1, P2 p2, P3 p3);

        /**
         * Constructs an object of type T by calling a
         * three argument constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 The first parameter to pass to the constructor.
         * \param p2 The second parameter to pass to the constructor.
         * \param p3 The third parameter to pass to the constructor.
         * \param p4 The fourth parameter to pass to the constructor.
         * \return A newly created object.
         */
        template<class P1, class P2, class P3, class P4>
        T& construct(P1 p1, P2 p2, P3 p3, P4 p4);

        /**
         * Constructs an object of type T by calling a
         * five argument constructor.
         * Uses placement new to construct the object into the memory
         * passed in the constructor.
         *
         * \param p1 The first parameter to pass to the constructor.
         * \param p2 The second parameter to pass to the constructor.
         * \param p3 The third parameter to pass to the constructor.
         * \param p4 The fourth parameter to pass to the constructor.
         * \param p5 The fifth parameter to pass to the constructor.
         * \return A newly created object.
         */
        template<class P1, class P2, class P3, class P4, class P5>
        T& construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5);

        /**
         * Cast operator for the underlying memory. This can
         * be used to provide custom placement new constructor
         * calls if necessary.
         */
        operator uint8_t*();
    private:
        uint8_t* _memory;
    };


/*
 *
 * Implementation
 *
 */

template<class T>inline
constructor<T>::constructor(uint8_t mem[])
:   _memory(mem)
{}


template<class T>inline
T&
constructor<T>::construct()
{
    return *new (_memory)T();
}

template<class T>
inline
T&
constructor<T>::construct(const T& p1)
{
    return *new (_memory)T(p1);
}

template<class T>
template<class P1>inline
T&
constructor<T>::construct(P1 p1)
{
    return *new (_memory)T(p1);
}

template<class T>
template<class P1, class P2>inline
T&
constructor<T>::construct(P1 p1, P2 p2)
{
    return *new (_memory)T(p1, p2);
}

template<class T>
template<class P1, class P2, class P3>inline
T&
constructor<T>::construct(P1 p1, P2 p2, P3 p3)
{
    return *new (_memory)T(p1, p2, p3);
}

template<class T>
template<class P1, class P2, class P3, class P4>inline
T&
constructor<T>::construct(P1 p1, P2 p2, P3 p3, P4 p4)
{
    return *new (_memory)T(p1, p2, p3, p4);
}

template<class T>
template<class P1, class P2, class P3, class P4, class P5>inline
T&
constructor<T>::construct(P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
    return *new (_memory)T(p1, p2, p3, p4, p5);
}

template<class T>inline
constructor<T>::operator uint8_t*()
{
    return _memory;
}

} /* namespace estd */
} /* namespace esrlabs */



#endif /* ESTD_CONSTRUCTOR_H */
