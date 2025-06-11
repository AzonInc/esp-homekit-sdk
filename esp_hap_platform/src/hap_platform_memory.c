#include <stdlib.h>
#include <stdbool.h>
#if CONFIG_IDF_TARGET_ESP32
#include "esp_heap_caps.h"
#include "esp_psram.h"
#endif

static bool psram_available(void) {
#if CONFIG_IDF_TARGET_ESP32
    return (esp_psram_is_initialized() && esp_psram_get_size() > 0);
#else
    return false;
#endif
}

void * hap_platform_memory_malloc(size_t size)
{
#if CONFIG_IDF_TARGET_ESP32
    if (psram_available()) {
        void *ptr = heap_caps_malloc(size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
        if (ptr) {
            return ptr;
        }
        // Fallback to internal RAM if PSRAM allocation fails
        return heap_caps_malloc(size, MALLOC_CAP_DEFAULT);
    } else {
        return heap_caps_malloc(size, MALLOC_CAP_DEFAULT);
    }
#else
    return malloc(size);
#endif
}

void * hap_platform_memory_calloc(size_t count, size_t size)
{
#if CONFIG_IDF_TARGET_ESP32
    if (psram_available()) {
        void *ptr = heap_caps_calloc(count, size, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
        if (ptr) {
            return ptr;
        }
        // Fallback to internal RAM if PSRAM allocation fails
        return heap_caps_calloc(count, size, MALLOC_CAP_DEFAULT);
    } else {
        return heap_caps_calloc(count, size, MALLOC_CAP_DEFAULT);
    }
#else
    return calloc(count, size);
#endif
}

void hap_platform_memory_free(void *ptr)
{
    free(ptr);
}
