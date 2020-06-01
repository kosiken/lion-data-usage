#ifndef _LDATA_H_
#define _LDATA_H_

#include <stdint.h>

typedef struct
{
    uint64_t recieved;

    uint64_t sent;
} ldata;

typedef struct
{
    ldata used;
    ldata snapshot;
    uint64_t remaining;
    char *ifa_name;
} dataUsage;

int parse_bytes(const char *str, uint64_t *result);

char *to_human_readable(double bytes, char *buf);

int mbs_poll_interfaces(dataUsage *d, ldata *stats);

int get_default_interface(char **ifa_name);

#endif //_HEADER_FILE_H_
