/**
 * Contains esrlabs::estd::nullptr_t.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_NULLPTR_H
#define ESTD_NULLPTR_H

namespace esrlabs {
namespace estd {

    /**
     * A C++11 like nullptr_t type. This is an improved way of handling
     * null pointers in C++.
     */
    class nullptr_t
    {
        struct _void {};
    public:
        /** Default constructor, creating a null pointer */
        nullptr_t();
        nullptr_t(int _void::*);
        
        /** void * cast */
        operator _void*() const;
        
        /** Template operator to cast to T* */
        template<class T>
        operator T*() const;

        /** Member function pointer cast */
        template<class T, class C>
        operator T C::*() const;

    private:
        void* _value;
    };

    /** Equality comparison, returns true */
    bool operator==(const nullptr_t&, const nullptr_t&);

    /** Not equals, returns false */
    bool operator!=(const nullptr_t&, const nullptr_t&);

    /** Less, returns false */
    bool operator< (const nullptr_t&, const nullptr_t&);

    /** Less or equal, returns true */
    bool operator<=(const nullptr_t&, const nullptr_t&);

    /** Greater, returns false */
    bool operator> (const nullptr_t&, const nullptr_t&);

    /** Greater or equal, returns true */
    bool operator>=(const nullptr_t&, const nullptr_t&);

} /* namespace estd */
} /* namespace esrlabs */

namespace esrlabs {
namespace estd {

inline
nullptr_t::nullptr_t()
:   _value(0L)
{}

inline
nullptr_t::nullptr_t(int _void::*)
:   _value(0L)
{}

inline
nullptr_t::operator _void*() const
{
    return 0L;
}

template<class T>
nullptr_t::operator T*() const
{
    return 0L;
}

template<class T, class C>
nullptr_t::operator T C::*() const
{
    return 0L;
}

inline bool
operator==(const nullptr_t&, const nullptr_t&)
{
    return true;
}

inline bool
operator!=(const nullptr_t&, const nullptr_t&)
{
    return false;
}

inline bool
operator<(const nullptr_t&, const nullptr_t&)
{
    return false;
}

inline bool
operator<=(const nullptr_t&, const nullptr_t&)
{
    return true;
}

inline bool
operator>(const nullptr_t&, const nullptr_t&)
{
    return false;
}

inline bool
operator>=(const nullptr_t&, const nullptr_t&)
{
    return true;
}

namespace internal
{
    /// \cond INTERNAL
    inline nullptr_t get_nullptr()
    {
        return nullptr_t(0);
    }
    /// \endcond
} /* namespace internal */

#undef nullptr
#define nullptr ::esrlabs::estd::internal::get_nullptr()

} /* namespace estd */

} /* namespace esrlabs */


#endif
