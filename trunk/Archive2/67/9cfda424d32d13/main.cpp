#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>

int main(int argc, char **argv)
{
    inquiry_info *ii = NULL;
    int max_rsp, num_rsp;
    int dev_id, sock, len, flags;
    int i, j;
    char addr[19] = { 0 };
    char oldaddr[20] = { 0 };
    char name[248] = { 0 };

    dev_id = hci_get_route(NULL);
    sock = hci_open_dev( dev_id );
    if (dev_id < 0 || sock < 0) {
        perror("opening socket");
        exit(1);
    }

    len  = 1;
    j = 0;
    max_rsp = 255;
    flags = IREQ_CACHE_FLUSH;
    while(len){
        ii = (inquiry_info*)malloc(max_rsp * sizeof(inquiry_info));
        num_rsp = hci_inquiry(dev_id, len, max_rsp, NULL, &ii, flags);
        if(num_rsp < 0){perror("hci_inquiry");}

        for (i = 0; i < num_rsp; i++) {
            ba2str(&(ii+i)->bdaddr, addr);
	    if(strcmp(addr,"D1:B2:77:8D:32:1B") == 0){
    		printf("SKATEBOARDER [1] GEIDENTIFICEERD \n");
    		goto out;
	    }else if(strcmp(addr,"B0:D0:9C:57:30:2C") == 0){
    		printf("SKATEBOARDER [3] GEIDENTIFCEERD \n");
    		goto out;
	    }
            //printf("%s  %s\n", addr, name);
        }
        free( ii );
	j++;
    }
out:
    close( sock );
    return 0;
}