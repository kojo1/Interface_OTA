#ifndef ZEPHYR_COMPAT_H_
#define ZEPHYR_COMPAT_H_

#include <netdb.h>

#ifdef __cplusplus
extern "C" {
#endif

struct hostent *gethostbyname(const char *name);

#ifdef __cplusplus
}
#endif

#endif
