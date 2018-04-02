#ifndef __TOOLS_H__
#define __TOOLS_H__

#include <onion/onion.h>
#include <onion/response.h>

int s_strcmp(const char *a, const char *b);

#define API_UNIMPLEMENTED onion_response_write0(res, "{\"status\": \"ko\", \"error\": \"unimplemented\"}"); return OCS_PROCESSED;

#endif /* __TOOLS_H__ */
