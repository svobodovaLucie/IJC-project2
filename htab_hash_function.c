#include "htab.h"
#include <stdint.h>

/**
 * @brief hash function
 * 
 * @param str string to be hashed
 * @return hash result
 */
size_t htab_hash_function(const char *str) {
    uint32_t h=0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++)
        h = 65599*h + *p;
    return h;
}
