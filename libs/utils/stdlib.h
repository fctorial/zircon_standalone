#include <zircon/types.h>
#include <stdarg.h>
typedef __SIZE_TYPE__ size_t;

int snprintf(char* str, size_t size, const char* format, ...);
int vsnprintf(char* str, size_t size, const char* format, va_list arg);
int strcmp(const char*, const char*);
void *memset(void *s, int c, size_t n);
const char* zx_status_get_string(zx_status_t status);
