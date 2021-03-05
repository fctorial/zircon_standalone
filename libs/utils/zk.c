#include <libs/linker/linker.h>
#include <libs/utils/stdlib.h>
#include <stdarg.h>
#include "zk.h"

int dprintf(const char *fmt, ...) {
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int result = vsnprintf(buf, 1024, fmt, args);
  zx_debug_write(buf, result);
  va_end(args);
  return result;
}

int dlog(char* key, char* fmt, ...) {
  int res1 = dprintf("%-40s", key);
  char buf[1024];
  va_list args;
  va_start(args, fmt);
  int res2 = vsnprintf(buf, 1024, fmt, args);
  zx_debug_write(buf, res2);
  zx_debug_write("\n", 1);
  va_end(args);
  return res1 + res2 + 1;
}

void print_strings(char* start, int num) {
  while (num--) {
    int read = dprintf("%s\n", start);
    start += read;
  }
}

const char* zx_status_get_string(zx_status_t status) {
  switch (status) {
    case ZX_OK:
      return "ZX_OK";
    case ZX_ERR_INTERNAL:
      return "ZX_ERR_INTERNAL";
    case ZX_ERR_NOT_SUPPORTED:
      return "ZX_ERR_NOT_SUPPORTED";
    case ZX_ERR_NO_RESOURCES:
      return "ZX_ERR_NO_RESOURCES";
    case ZX_ERR_NO_MEMORY:
      return "ZX_ERR_NO_MEMORY";
    case ZX_ERR_INTERNAL_INTR_RETRY:
      return "ZX_ERR_INTERNAL_INTR_RETRY";
    case ZX_ERR_INVALID_ARGS:
      return "ZX_ERR_INVALID_ARGS";
    case ZX_ERR_BAD_HANDLE:
      return "ZX_ERR_BAD_HANDLE";
    case ZX_ERR_WRONG_TYPE:
      return "ZX_ERR_WRONG_TYPE";
    case ZX_ERR_BAD_SYSCALL:
      return "ZX_ERR_BAD_SYSCALL";
    case ZX_ERR_OUT_OF_RANGE:
      return "ZX_ERR_OUT_OF_RANGE";
    case ZX_ERR_BUFFER_TOO_SMALL:
      return "ZX_ERR_BUFFER_TOO_SMALL";
    case ZX_ERR_BAD_STATE:
      return "ZX_ERR_BAD_STATE";
    case ZX_ERR_TIMED_OUT:
      return "ZX_ERR_TIMED_OUT";
    case ZX_ERR_SHOULD_WAIT:
      return "ZX_ERR_SHOULD_WAIT";
    case ZX_ERR_CANCELED:
      return "ZX_ERR_CANCELED";
    case ZX_ERR_PEER_CLOSED:
      return "ZX_ERR_PEER_CLOSED";
    case ZX_ERR_NOT_FOUND:
      return "ZX_ERR_NOT_FOUND";
    case ZX_ERR_ALREADY_EXISTS:
      return "ZX_ERR_ALREADY_EXISTS";
    case ZX_ERR_ALREADY_BOUND:
      return "ZX_ERR_ALREADY_BOUND";
    case ZX_ERR_UNAVAILABLE:
      return "ZX_ERR_UNAVAILABLE";
    case ZX_ERR_ACCESS_DENIED:
      return "ZX_ERR_ACCESS_DENIED";
    case ZX_ERR_IO:
      return "ZX_ERR_IO";
    case ZX_ERR_IO_REFUSED:
      return "ZX_ERR_IO_REFUSED";
    case ZX_ERR_IO_DATA_INTEGRITY:
      return "ZX_ERR_IO_DATA_INTEGRITY";
    case ZX_ERR_IO_DATA_LOSS:
      return "ZX_ERR_IO_DATA_LOSS";
    case ZX_ERR_IO_NOT_PRESENT:
      return "ZX_ERR_IO_NOT_PRESENT";
    case ZX_ERR_IO_OVERRUN:
      return "ZX_ERR_IO_OVERRUN";
    case ZX_ERR_IO_MISSED_DEADLINE:
      return "ZX_ERR_IO_MISSED_DEADLINE";
    case ZX_ERR_IO_INVALID:
      return "ZX_ERR_IO_INVALID";
    case ZX_ERR_BAD_PATH:
      return "ZX_ERR_BAD_PATH";
    case ZX_ERR_NOT_DIR:
      return "ZX_ERR_NOT_DIR";
    case ZX_ERR_NOT_FILE:
      return "ZX_ERR_NOT_FILE";
    case ZX_ERR_FILE_BIG:
      return "ZX_ERR_FILE_BIG";
    case ZX_ERR_NO_SPACE:
      return "ZX_ERR_NO_SPACE";
    case ZX_ERR_NOT_EMPTY:
      return "ZX_ERR_NOT_EMPTY";
    case ZX_ERR_STOP:
      return "ZX_ERR_STOP";
    case ZX_ERR_NEXT:
      return "ZX_ERR_NEXT";
    case ZX_ERR_ASYNC:
      return "ZX_ERR_ASYNC";
    case ZX_ERR_PROTOCOL_NOT_SUPPORTED:
      return "ZX_ERR_PROTOCOL_NOT_SUPPORTED";
    case ZX_ERR_ADDRESS_UNREACHABLE:
      return "ZX_ERR_ADDRESS_UNREACHABLE";
    case ZX_ERR_ADDRESS_IN_USE:
      return "ZX_ERR_ADDRESS_IN_USE";
    case ZX_ERR_NOT_CONNECTED:
      return "ZX_ERR_NOT_CONNECTED";
    case ZX_ERR_CONNECTION_REFUSED:
      return "ZX_ERR_CONNECTION_REFUSED";
    case ZX_ERR_CONNECTION_RESET:
      return "ZX_ERR_CONNECTION_RESET";
    case ZX_ERR_CONNECTION_ABORTED:
      return "ZX_ERR_CONNECTION_ABORTED";
    default:
      return "(UNKNOWN)";
  }
}

