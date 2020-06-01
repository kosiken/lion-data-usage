#ifndef _LDATA_H_
#define _LDATA_H_

#include <stdint.h>

// holds data usage stats
typedef struct
{
    uint64_t recieved;

    uint64_t sent;
} ldata;

// class used to interface with os to get data usage info
typedef struct
{
    ldata used;
    ldata snapshot;
    uint64_t remaining;
    char *ifa_name;
} dataUsage;



// converts a data usage bytes to an easier to read form
char *to_human_readable(double bytes, char *buf);
// continously polls to get the current data usage info
int mbs_poll_interfaces(dataUsage *d, ldata *stats);
// gets the name of the network hardware being used
int get_default_interface(char **ifa_name);

#endif //_HEADER_FILE_H_
