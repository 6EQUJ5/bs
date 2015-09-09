#ifndef _MODULE_BIT_STRING_H_
#define _MODULE_BIT_STRING_H_

#include <stddef.h>
#include <stdio.h>

#ifdef MODULE_BIT_STRING_IMPORT
    #define EXTERN
#else
    #define EXTERN extern
#endif

/* Tyep declarations follow */
typedef struct _module_bit_string_opaque bit_string;

/* Function prototypes */
// EXTERN void bit_string_module_init(void);
/* Initialize this module */

// EXTERN void bit_string_module_free(void);
/* Release internal data structures. */

EXTERN bit_string* bit_string_alloc(size_t);
EXTERN void bit_string_free(bit_string*);

EXTERN size_t bit_string_length (bit_string*);

EXTERN bit_string * bit_string_resize (bit_string *, size_t);

EXTERN bit_string * bit_string_set_bit (bit_string*,size_t);
EXTERN bit_string * bit_string_set_bits (bit_string*,...);
EXTERN bit_string * bit_string_not (bit_string *);
EXTERN bit_string * bit_string_and (bit_string *, bit_string *);

/* print a format string by also handling a new conversion 
 * specifier for the new type
 * the new conversion specifier is q */
EXTERN int bit_string_fprintf(FILE*, const char* ,...);
EXTERN int bit_string_vfprintf(FILE*, const char *, va_list);

#undef MODULE_BIT_STRING_IMPORT
#undef EXTERN
#endif 

