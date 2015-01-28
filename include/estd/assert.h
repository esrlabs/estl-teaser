/**
 * Contains assert macros and classes.
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */
#ifndef ESTD_ASSERT_H
#define ESTD_ASSERT_H

#if defined(ESTL_USE_STANDARD_ASSERT)
#include <cassert>

#elif defined(ESTL_USE_STANDARD_ASSERT)
#  define estd_assert(E__) assert(E__)

#elif defined(ESTL_NO_ASSERT_FILE)
#  define estd_assert(E__) \
    ((E__) ? (void)0 : esrlabs::estd::assert_func((const char *)0, __LINE__, #E__))

#elif defined(ESTL_NO_ASSERT_FILE_LINE)
#  define estd_assert(E__) \
    ((E__) ? (void)0 : esrlabs::estd::assert_func((const char *)0, 0, #E__))

#elif defined(ESTL_ASSERT_MESSAGE_ALL)
#  define estd_assert(E__) \
    ((E__) ? (void)0 : esrlabs::estd::assert_func(__FILE__, __LINE__, #E__))

#elif defined(ESTL_NO_ASSERT_MESSAGE)
#  define estd_assert(E__) \
    ((E__) ? (void)0 : esrlabs::estd::assert_func((const char *)0, 0, (const char *)0))

#elif defined(ESTL_NO_ASSERT)
#  define estd_assert(E__) ((void)0)
#endif

// if no assert style is picked then we will use the "default" one.
#ifndef estd_assert
#  define estd_assert(E__) \
    ((E__) ? (void)0 : esrlabs::estd::assert_func((const char *)0, __LINE__, #E__))
#endif

namespace esrlabs {
namespace estd {

extern void assert_func(const char * /* file */,
        int/* line */, const char * /* test */);

/*
 * Assert Handler function
 */
typedef void (*AssertHandler)(const char * /* file */,
        int /* line */, const char * /* test */);

extern void set_assert_handler(AssertHandler);

extern AssertHandler get_assert_handler();

/*
 * Two pre-defined assert handlers.
 */

/*
 * Default one. Just calls assert(0)
 */
extern void AssertDefaultHandler(const char * /* file */,
        int /* line */, const char * /* test */);

/*
 * This one throws the assert_exception
 */
extern void AssertExceptionHandler(const char * /* file */,
        int /* line */, const char * /* test */);

/*
 * An exception that is thrown with the assert.
 */
class assert_exception {

public:

    assert_exception(const char *file, int line, const char *test);

    const char *getFile() const;
    int getLine() const;
    const char *getTest() const;

private:

    const char *_file;
    int _line;
    const char *_test;

};

/*
 * Class to acquire and release the assertion handler
 */
class AssertHandlerScope {

public:

    AssertHandlerScope(AssertHandler next);
    ~AssertHandlerScope();

private:

    AssertHandler _current;

};

} /* namespace estd */

} /* namespace esrlabs */

#endif /* ESTD_ASSERT_H */
