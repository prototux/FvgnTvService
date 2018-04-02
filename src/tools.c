#include <inttypes.h>
#include <string.h>

#include <onion/onion.h>
#include <onion/response.h>

int s_strcmp(const char *a, const char *b)
{
    if (!a && !b)
        return 1;
    if (!a || !b)
        return 0;
    return strcmp(a,b)==0;
}
