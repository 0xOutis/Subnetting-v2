#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "subnet.h"

int host;
int network=0,broadcast=0;
int numbers=1;

void help() {
	puts("Options: ");
	puts("\t#--classC or -cC");
	puts("\t\tPrefix: 24 - 30");
	puts("\t#--classB or -cB");
	puts("\t\tPrefix: 16 - 23, 24 - 30");
	puts("\t#--classA or -cA");
	puts("\t\tPrefix: 8 - 15, 16 - 23, 24 - 30");
	puts("Examples:");
	puts("IP address Class C: ./subnet 192.168.10.1/24 --classC");
	puts("IP address Class B: ./subnet 172.16.10.22/16 --classB");
	puts("IP address Class A: ./subnet 10.10.1.1/8 --classA");
}

void moveBuffer(void *buffer, ipaddr_t *ip) {
	char *address = (char*)malloc(32*sizeof(char));
        strcpy(address, buffer);
        char tmp[3];
        short y=0, x=0;

        for (int i=0;i<strlen(address);i++) {
                if ((address[i] != __DOT_) && (address[i] != __PREFIX_)) {
			tmp[x] = address[i];
			x++;
                }
                else if ((address[i] == __DOT_) || (address[i] == __PREFIX_)) {
			ip->octet[y] = atoi(tmp);
                        memset(tmp,CLEAN_BUFFER,sizeof(tmp));
                        x=CLEAN_BUFFER;
                        y++;
                        if (address[i] == __PREFIX_) {
                                for (int j=(i+1);j<=strlen(address);j++) {
                                        tmp[x] = address[j];
                                        x++;
                                }
                                ip->prefix = atoi(tmp);
                                free(address);
                                break;
                        }
                }
        }	
}

void prefix24_30(ipaddr_t *ip) {

	ip->object.grade[0] = 32 - ip->prefix;
	ip->object.subnet[0] = pow (2, ip->object.grade[0]);
	ip->object.mask = 256 - ip->object.subnet[0];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0], ip->octet[1], ip->octet[2], ip->octet[3]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, 0xff, 0xff, ip->object.mask);
	host = ip->object.subnet[0] - 2;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d.%d."BOLDRED"%d\t"WHT, ip->octet[0], ip->octet[1], ip->octet[2], network);
		network += ip->object.subnet[0];
		broadcast = network - 1;
		printf("  -\t%d.%d.%d."BOLDRED"%d\t"WHT"->[%d]\n", ip->octet[0], ip->octet[1], ip->octet[2], broadcast, numbers);
		numbers++;
	} while(network <= 0xff);
	LINE
}

void prefix16_23(ipaddr_t *ip) {

	ip->object.grade[0] = 32 - ip->prefix;
	ip->object.grade[1] = 24 - ip->prefix;
	ip->object.subnet[0] = pow (2, ip->object.grade[0]);
	ip->object.subnet[1] = pow (2, ip->object.grade[1]);
	ip->object.mask = 256 - ip->object.subnet[1];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0], ip->octet[1], ip->octet[2], ip->octet[3]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, 0xff, ip->object.mask, 0x00);
	host = ip->object.subnet[0] - 2;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d."BOLDRED"%d.%d\t"WHT, ip->octet[0], ip->octet[1], network, 0x00);
		network += ip->object.subnet[1];
		broadcast = network - 1;
		printf("  -\t%d.%d."BOLDRED"%d.%d\t"WHT"->[%d]\n", ip->octet[0], ip->octet[1], broadcast, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	LINE
}

void prefix8_15(ipaddr_t *ip) {

	ip->object.grade[0] = 32 - ip->prefix;
	ip->object.grade[1] = 16 - ip->prefix;
	ip->object.subnet[0] = pow (2, ip->object.grade[0]);
	ip->object.subnet[1] = pow (2, ip->object.grade[1]);
	ip->object.mask = 256 - ip->object.subnet[1];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0], ip->octet[1], ip->octet[2], ip->octet[3]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, ip->object.mask, 0x00, 0x00);
	host = ip->object.subnet[0] - 2;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d."BOLDRED"%d.%d.%d\t"WHT, ip->octet[0], network, 0x00, 0x00);
		network += ip->object.subnet[0x1];
		broadcast = network - 1;
		printf(" -\t%d."BOLDRED"%d.%d.%d\t"WHT"->[%d]\n", ip->octet[0], broadcast, 0xff, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	LINE
}
