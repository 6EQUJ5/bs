#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <malloc.h>
#include <stddef.h>

/* Including our own header: */
#define MODULE_BIT_STRING_IMPORT
#include "bit.string.h"

/* Public opaque types */
typedef struct _module_bit_string_opaque
{
    unsigned char * internal_string;
    unsigned char carry;
    size_t length;
} bit_string;

/* Private functions */
static void _init_to_zero(bit_string* bstr) {
    
    size_t index, bstr_length = bstr -> length;
    unsigned char * value = bstr -> internal_string;
    for (index = 0; index < bstr_length; index++)
        value [index] = 0x00;

}

static char * _to_string (bit_string* bstr) {
    size_t index, bstr_length = bstr -> length;
    const unsigned char const * value = bstr -> internal_string;
    char * ret_val = malloc (sizeof(char) * ( 1 + bstr_length));
    ret_val[bstr_length] = '\0';
    for (index = 0; index < bstr_length; index++ ) 
        ret_val [bstr_length - 1 - index] = value [index] == 0 ? '0' : '1';

    return ret_val;
}
 
/* Public functions */
bit_string* bit_string_alloc(size_t size) {
    bit_string* intern = malloc(sizeof(bit_string));
    intern -> internal_string = malloc(sizeof(unsigned char) * size);
    intern -> length = size;
    _init_to_zero(intern);

    return intern;
}

void bit_string_free (bit_string* bstr) {
    free(bstr -> internal_string);
    free(bstr);
}

size_t bit_string_length (bit_string* bs) {
    return bs -> length;
}

bit_string * bit_string_set_bit (bit_string* bstr,size_t position) {
    size_t bstr_length = bstr -> length;
    unsigned char * bstr_intern = bstr -> internal_string;
    if (position < 0 || position >= bstr_length)
        return bstr;
    bstr_intern [ position ] = 0x01;

    return bstr;
}

bit_string * bit_string_set_bits (bit_string* bs,...) {
    va_list args;
    size_t bit, bs_len = bs -> length;

    va_start (args, bs);
    while(1) {
        bit = va_arg(args, size_t);
        if (bit >= bs_len)
            break;
        bit_string_set_bit(bs, bit);
    }
    va_end (args);

    return bs;
}

bit_string * bit_string_not (bit_string * bstr) {
    size_t index, bstr_length = bstr -> length;
    unsigned char * bstr_intern = bstr -> internal_string;
    for (index = 0; index < bstr_length; index++)
        bstr_intern[index] = 
            bstr_intern[index] == 0x00 ? 0x01 : 0x00;

    return bstr;
}

bit_string * bit_string_and (bit_string * bs1, bit_string * bs2) {
    size_t index = 0, bsl1, bsl2;
    bsl1 = bs1 -> length;
    bsl2 = bs2 -> length;
    unsigned char * bsint1 = bs1 -> internal_string;
    unsigned char * bsint2 = bs2 -> internal_string;
    for (; index < bsl1 && index < bsl2; index++)
        bsint1[index] = (bsint1[index] != 0x00 && bsint2[index] != 0x00) ?
            0x01 : 0x00;

    return bs1;
}

int bit_string_fprintf(FILE* stream, const char* format,...) {
    va_list ap;
    int ret_val;

    va_start(ap, format);
    ret_val = bit_string_vfprintf(stream, format, ap);
    va_end(ap);

    return ret_val;
}

int bit_string_vfprintf(FILE* stream, const char *format, va_list args) {
    int ret_val = 0;
    char * bit_string_value;
    char * tag = "%q"; /* q is the new conversion specifier */

    /* we need to copy the format string because we will
       be splitting it in inserting NULL limiters in place of the 
       new conversion specifier
       further more we will be using it for iteration */
    char * tmp_format = malloc((1 + strlen(format)) * sizeof(char));

    /* we need a copy of it for after we have finished with
       the itteration too free the allocated string */
    char * beginning = tmp_format;

    strcpy (tmp_format, format);

    /* another temporal pointer used for the itteration */
    char * pntr;

    /* used to catch the bit stream argument */
    bit_string * bstr;

    /* while we are still finding q convertion specs */
    while ( (pntr = strstr(tmp_format, tag)) != NULL)  {
        /* limit the format string to before the conversion spec */
        *pntr = '\0';

        /* pass the 'generic' format string to the 'generic' function */
        ret_val += vprintf(tmp_format, args);

        /* print the the bit string */
        bstr = va_arg(args, bit_string*);
        bit_string_value = _to_string(bstr);
        ret_val += printf ("%s", bit_string_value);
        free (bit_string_value);

        /* iterate */
        tmp_format = pntr + (sizeof(char))* strlen(tag);
    }
    // if (strlen(tmp_format) > 0)
        //printf("%s\n", tmp_format);
    /* print what is left of the 'generic' arguments */
    ret_val += vprintf(tmp_format, args);

    /* free the copied string */
    free (beginning); 
    return ret_val;
}

   

