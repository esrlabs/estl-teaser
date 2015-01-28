/**
 * Contains internal type traits
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_TYPE_TRAITS_H
#define ESTD_TYPE_TRAITS_H

#include <estd/estdint.h>

namespace esrlabs {
namespace estd {

    template<bool C, class T = void> struct enable_if {};
    
    template<class T> struct enable_if<true, T> { typedef T type; };
    
    template<bool C, class T, class F> struct conditional { typedef T type; };
    template<class T, class F> struct conditional<false, T, F> { typedef F type; };
    
    namespace internal
    {
        /// \cond INTERNAL
        typedef char _true;
        struct _false { char _[2]; };
        /// \endcond
    } /* namespace internal */
    
    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() const { return v; };
    };
    
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;
    
    template<class T> struct remove_reference           { typedef T type; };
    template<class T> struct remove_reference<T&>       { typedef T type; };
    
    template<class T> struct add_reference              { typedef T& type; };
    template<class T> struct add_reference<T&>          { typedef T& type; };
    
    template<class T> struct remove_const               { typedef T type; };
    template<class T> struct remove_const<const T>      { typedef T type; };
    
    template<class T> struct remove_volatile            { typedef T type; };
    template<class T> struct remove_volatile<volatile T>{ typedef T type; };
    
    template<class T> struct remove_cv
    { typedef typename remove_const<typename remove_volatile<T>::type>::type type; };
    
    template<class T> struct is_void : public false_type {};
    template<> struct is_void<void>  : public true_type {};
    
    template<class T> struct is_array                   : public false_type {};
    template<class T> struct is_array<T[]>              : public true_type {};
    template<class T, size_t N> struct is_array<T[N]>   : public true_type {};
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> struct _is_pointer     : public false_type {};
        template<class T> struct _is_pointer<T*> : public true_type {};
        /// \endcond
    }
    
    template<class T> struct is_pointer : internal::_is_pointer<typename remove_cv<T>::type> {};
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> struct _is_reference     : public false_type {};
        template<class T> struct _is_reference<T&> : public true_type {};
        /// \endcond
    }
    
    template<class T> struct is_reference : internal::_is_reference<typename remove_cv<T>::type> {};
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> _true  _is_class_test(int T::*);
        template<class T> _false _is_class_test(...);
        /// \endcond
    }
    
    template<class T>
    struct is_class : public integral_constant<bool, (sizeof(internal::_is_class_test<T>(0)) == sizeof(internal::_true))>{ };
    
    template<class T, class X> struct is_same   : public false_type {};
    template<class T> struct is_same<T, T>      : public true_type {};
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> _true _is_base_of_test(T*);
        template<class T> _false _is_base_of_test(...);
        /// \endcond
    }
    
    template<class B, class D>
    struct is_base_of : public integral_constant<bool, (sizeof(internal::_is_base_of_test<typename remove_cv<B>::type>(reinterpret_cast<typename remove_cv<D>::type*>(0L))) == sizeof(internal::_true))>{ };
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> _true _is_function_test(T*);
        template<class T> _false _is_function_test(...);
        template<class T> T& _is_function_test_argument();
        
        template<class T, bool = !is_void<T>::value && !is_reference<T>::value && !is_class<T>::value>
        struct _is_function : public integral_constant<bool, sizeof(_is_function_test<T>(_is_function_test_argument<T>())) == sizeof(_true)> {};
        
        template<class T>
        struct _is_function<T, false> : public false_type {};
        /// \endcond
    }
    
    template<class T> struct is_function : public internal::_is_function<T> {};
    
    namespace internal
    {
        /// \cond INTERNAL
        template<class T> struct _is_member_function_pointer : public false_type {};
        template<class T, class F> struct _is_member_function_pointer<T F::*> : public is_function<T> {};
        /// \endcond
    }
    
    template<class T> struct is_member_function_pointer : public internal::_is_member_function_pointer<typename remove_cv<T>::type> {};

    template<class T> struct is_integral : false_type {};
    template<> struct is_integral<bool> : true_type {};
    template<> struct is_integral<char> : true_type {};
    template<> struct is_integral<signed char> : true_type {};
    template<> struct is_integral<short int> : true_type {};
    template<> struct is_integral<int> : true_type {};
    template<> struct is_integral<long int> : true_type {};
    template<> struct is_integral<uint8_t> : true_type {};
    template<> struct is_integral<uint16_t> : true_type {};
    template<> struct is_integral<uint32_t> : true_type {};
    template<> struct is_integral<uint64_t> : true_type {};

} /* namespace estd */

} /* namespace esrlabs */

#endif
