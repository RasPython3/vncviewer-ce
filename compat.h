#ifndef COMPAT_H
#define COMPAT_H

#ifndef _MSC_VER

#ifndef min
#define min(x, y) ((x)<(y)?(x):(y))
#endif
#ifndef max
#define max(x, y) ((x)>(y)?(x):(y))
#endif

#ifdef __cplusplus

#include <exception>
#include <windows.h>

#define log log_

using namespace std;

class __compat_exception : public exception {
public:
  DWORD code;
  __compat_exception();
  __compat_exception(DWORD code, DWORD flags, DWORD nargs, const ULONG_PTR *args);
  const char* what() const noexcept override;
};

class __compat_handling_exception: public __compat_exception {
public:
  __compat_handling_exception& operator=(const __compat_exception& e);
};

void _RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ULONG_PTR *lpArguments);
DWORD _GetExceptionCode(void);

#ifdef __try
#undef __try
#endif
#ifdef __except
#undef __except
#endif

#define __try try
#define __except(x) \
  catch (__compat_exception& __err) { \
    __compat_handling_exception __cur_err; \
    __cur_err = __err; \
    if ((x)) { \
      throw __cur_err; \
    } else { \
      throw __err; \
    } \
  } catch (__compat_handling_exception& __cur_err)

#ifdef RaiseException
#undef RaiseException
#endif
#define RaiseException _RaiseException

#ifdef GetExceptionCode
#undef GetExceptionCode
#endif
#define GetExceptionCode _GetExceptionCode

#endif /* __cplusplus */

#endif /* !_MSC_VER */

#endif /* COMPAT_H */
