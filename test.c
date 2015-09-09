#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "bit.string.h"

int main(int argc, char** argv)
{
    bit_string* bstr1 = bit_string_alloc(28);
    bit_string* bstr2 = bit_string_alloc(19);
    bit_string_set_bit (bstr1, 13);
    bit_string_set_bits (bstr2, 4, 7, 11, 12, bit_string_length(bstr2));

    bit_string_fprintf(stderr, "%c%q%c\n",'[', bstr1, ']');
    bit_string_fprintf(stderr, "%c%q%c\n",'[', bstr2, ']');

    bit_string_fprintf(stderr, "%c%q%c\n",'[', 
            bit_string_not(bstr1), ']');
    bit_string_fprintf(stderr, "%c%q%c\n",'[', 
            bit_string_and(bstr1, bstr2), ']');
    bit_string_fprintf(stderr, "%c%q%c\n",'[', 
            bit_string_not(bstr1), ']');

    bit_string_resize(bit_string_resize(bstr1, 17), 23);

    bit_string_fprintf(stderr, "%c%q%c\n",'[', bstr1, ']');

    bit_string_free(bstr1);
    bit_string_free(bstr2);

    return 0;
}


