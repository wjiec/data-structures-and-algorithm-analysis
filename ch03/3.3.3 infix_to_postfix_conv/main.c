#include <stdio.h>
#include <stdlib.h>
#include "i_p_conv.h"

int main(void) {
    char *string = "a + b * c + (d * c + f) * g";
    char *output = infix_to_postfix_conv(string);

    puts(output);
    free(output);
    return 0;
}
