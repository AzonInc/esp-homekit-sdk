#ifndef _HAP_PLATFORM_MEMORY_H_
#define _HAP_PLATFORM_MEMORY_H_
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Allocate memory, using PSRAM if available on ESP32 */
void * hap_platform_memory_malloc(size_t size);

/** Allocate contiguous memory for items, using PSRAM if available on ESP32 */
void * hap_platform_memory_calloc(size_t count, size_t size);

/** Free allocated memory */
void hap_platform_memory_free(void *ptr);

#ifdef __cplusplus
}
#endif
#endif /* _HAP_PLATFORM_MEMORY_H_ */
