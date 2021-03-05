int dprintf(const char *fmt, ...);

int dlog(char *key, char *fmt, ...);

void print_strings(char *start, int num);

const char* zx_status_get_string(zx_status_t status);
