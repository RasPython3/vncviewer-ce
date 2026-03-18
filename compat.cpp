#include <windows.h>

#include "compat.h"

DWORD curcode = 0;

__compat_exception::__compat_exception() {
  this->code = 0;
}

__compat_exception::__compat_exception(DWORD code, DWORD flags, DWORD nargs, const ULONG_PTR *args) {
  this->code = code;
}

const char* __compat_exception::what() const noexcept {
  char ecode[16];
  sprintf(ecode, "0x%08X", (unsigned int)code);

  return (const char*)ecode;
}

__compat_handling_exception& __compat_handling_exception::operator=(const __compat_exception& e) {
  curcode = e.code;
  this->code = curcode;
  return *this;
}

void _RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags, DWORD nNumberOfArguments, const ULONG_PTR *lpArguments) {
  throw __compat_exception(dwExceptionCode, dwExceptionFlags, nNumberOfArguments, lpArguments);
}

DWORD _GetExceptionCode(void) {
  return curcode;
}
