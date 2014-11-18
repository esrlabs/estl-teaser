/**
 * \file
 * \ingroup estl
 * \copyright   E.S.R.Labs AG, 2014, All rights reserved.
 */

#include <cassert>

#include <estd/assert.h>

namespace esrlabs {
namespace estd {

static AssertHandler& global_assert_handler()
{
    static AssertHandler global_assert_handler = AssertDefaultHandler;
    return global_assert_handler;
}

void
assert_func(const char *file, int line, const char *test)
{
    if(global_assert_handler() != 0) {
        global_assert_handler()(file, line, test);
    }
}

/*
 * Assert handlers
 */
void
set_assert_handler(AssertHandler handler)
{
    global_assert_handler() = handler;
}

AssertHandler
get_assert_handler()
{
    return global_assert_handler();
}

void
AssertDefaultHandler(const char *file, int line, const char *test)
{
#if 0
    if(file != 0) {
        fprintf(stderr, "[%s:%d] %s\n", file, line, test);
    }
#endif
    assert(0);
}

void
AssertExceptionHandler(const char *file, int line, const char *test)
{
#ifdef ESTD_HAS_EXCEPTIONS
    throw assert_exception(file, line, test);
#else
    assert(0);
#endif
}

/*
 * assert_exception
 */

assert_exception::assert_exception(const char *file, int line, const char *test)
: _file(file)
, _line(line)
, _test(test)
{

}

const char *
assert_exception::getFile() const
{
    return _file;
}

int
assert_exception::getLine() const
{
   return _line;
}

const char *
assert_exception::getTest() const
{
    return _test;
}

/*
 * AssertHandlerScope. Implements the RAII pattern.
 */

AssertHandlerScope::AssertHandlerScope(AssertHandler next)
{
    _current = get_assert_handler();
    set_assert_handler(next);
}

AssertHandlerScope::~AssertHandlerScope()
{
    set_assert_handler(_current);
}

} /* namespace estd */

} /* namespace esrlabs */
