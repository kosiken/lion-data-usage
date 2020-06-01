#define _DEFAULT_SOURCE
#define __STDC_FORMAT_MACROS

#include <ifaddrs.h>
#include <inttypes.h>
#include <limits.h>
#include <linux/if_link.h>
#include <net/if.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dataUsage.h"

int get_default_interface(char **ifa_name)
{
    struct ifaddrs *ifa0, *ifa;

    if (getifaddrs(&ifa0) == -1)
    {
        
        perror("error getting ifaddress");

        return -1;
    }
    for (ifa = ifa0; ifa != NULL; ifa = ifa->ifa_next)
    {
      
        const unsigned short sa_family = ifa->ifa_addr->sa_family;
        const int ifa_running = ifa->ifa_flags & IFF_RUNNING;

        if (NULL == ifa->ifa_addr)
            continue;

        if (sa_family != AF_INET && sa_family != AF_INET6)
            continue;

        if ((strcmp("lo", ifa->ifa_name) == 0) || !ifa_running)
            continue;
    
    
        *ifa_name = strdup(ifa->ifa_name);

        freeifaddrs(ifa0);
        return 0;
    }

    freeifaddrs(ifa0);
    return -1;
}

char *
to_human_readable(double bytes, char *buf)
{
    const char *units[] = {"B", "K", "M", "G", "T"};
    int i = 0;

    while (bytes >= 1024)
    {
        bytes /= 1024;
        ++i;
    }

    sprintf(buf, "%.*f%s", i, bytes, units[i]);
    return buf;
}

int mbs_poll_interfaces(dataUsage *s, ldata *stats)
{
    struct ifaddrs *ifa0, *ifa;

    if (getifaddrs(&ifa0) == -1)
    {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    for (ifa = ifa0; ifa != NULL; ifa = ifa->ifa_next)
    {
        const unsigned short int sa_family = ifa->ifa_addr->sa_family;

        if (sa_family == AF_PACKET && 0 == strcmp(ifa->ifa_name, s->ifa_name))
        {
            const struct rtnl_link_stats *if_stats = ifa->ifa_data;

            stats->recieved = if_stats->rx_bytes;
            stats->sent = if_stats->tx_bytes;

            freeifaddrs(ifa0);
            return 0;
        }
    }

    freeifaddrs(ifa0);
    return -1;
}