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

    class nullptr_t
    {
        struct _void {};
    public:
        nullptr_t();
        nullptr_t(int _void::*);
        
        operator _void*() const;
        
        template<class T>
        operator T*() const;

        template<class T, class C>
        operator T C::*() const;

        friend bool operator==(nullptr_t, nullptr_t);
        friend bool operator!=(nullptr_t, nullptr_t);
        friend bool operator< (nullptr_t, nullptr_t);
        friend bool operator<=(nullptr_t, nullptr_t);
        friend bool operator> (nullptr_t, nullptr_t);
        friend bool operator>=(nullptr_t, nullptr_t);
    private:
        void* _value;
    };
    
    inline nullptr_t::nullptr_t()
    :   _value(0L)
    {}
    
    inline nullptr_t::nullptr_t(int _void::*)
    :   _value(0L)
    {}
    
    inline nullptr_t::operator _void*() const
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
    
    inline bool operator==(nullptr_t, nullptr_t) { return true;  }
    inline bool operator!=(nullptr_t, nullptr_t) { return false; }
    inline bool operator< (nullptr_t, nullptr_t) { return false; }
    inline bool operator<=(nullptr_t, nullptr_t) { return true;  }
    inline bool operator> (nullptr_t, nullptr_t) { return false; }
    inline bool operator>=(nullptr_t, nullptr_t) { return true;  }

    
    namespace internal
    {
        inline nullptr_t get_nullptr()
        {
            return nullptr_t(0);
        }
    }

    #undef nullptr
    #define nullptr ::esrlabs::estd::internal::get_nullptr()

} /* namespace estd */

} /* namespace esrlabs */


#endif
