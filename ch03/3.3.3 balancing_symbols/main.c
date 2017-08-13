#include <assert.h>
#include "balancing_symbols.h"


int main(void) {
    char *string1 = "{{[[(())]]}}";
    assert(balancing_symbols(string1) == true);

    char *string2 = "{{}]";
    assert(balancing_symbols(string2) == false);

    return 0;
}
