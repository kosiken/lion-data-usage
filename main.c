#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "dataUsage.h"

int main()
{
    //  char *buf;
    // int i = 3;
    // const char *units[] = {"B", "K", "M", "G", "T"};
    // float bytes =  5;
    // sprintf ( buf,"%.*f%s", i, bytes, units[i]);
    dataUsage *d = (dataUsage *)malloc(sizeof(dataUsage));

    char *sent;
    char recieved[10];

    int p = get_default_interface(&(d->ifa_name));
    while (1)
    {
        mbs_poll_interfaces(d, &(d->snapshot));

        to_human_readable(d->snapshot.recieved, recieved);

        printf("%s\r", recieved);
        
       // break;
    }
    // printf("%s %d", //d->ifa_name, d->snapshot.recieved);
    free(d);
    
    // printf("%s", strlen(d->ifa_name));
    return 0;
}