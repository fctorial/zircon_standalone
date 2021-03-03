#include <zircon/types.h>
#include <stdarg.h>

int snprintf(char* str, size_t size, const char* format, ...);
int vsnprintf(char* str, size_t size, const char* format, va_list arg);
