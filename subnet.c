#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "subnet.h"

int host;
int network=0,broadcast=0;
int numbers=1;

void moveBuffer(char *buffer, ipaddr *__addr) {
	char address[0x1c];
	strcpy(address, buffer);
	char *tmp = (char*)malloc(0x03*sizeof(char));
	int y=0, x=0;

	for (int i=0;i<strlen(address);i++) {
		if ((address[i] != __DOT_) && (address[i] != __PREFIX_)) {
			tmp[x] = address[i];
			x++;
		} else if ((address[i] == __DOT_) || (address[i] == __PREFIX_)) {
			__addr->octet[y] = atoi(tmp);
			memset(tmp, 0x00, sizeof(&tmp));
			x=0;
			y++;
			if (address[i] == __PREFIX_) {
				for (int j=(i+0x01);j<=strlen(address);j++) {
					tmp[x] = address[j];
					x++;
				}
				__addr->prefix = atoi(tmp);
				free(tmp);
				break;
			}
		}
	}
}

void prefix24_30(ipaddr *ip) {
	object obj;

	obj.grade[0x00] = 0x20 - ip->prefix;
	obj.subnet[0x00] = pow (2, obj.grade[0x00]);
	obj.mask = 0x100 - obj.subnet[0x00];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], ip->octet[0x03]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, 0xff, 0xff, obj.mask);
	host = obj.subnet[0x00] - 0x02;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d.%d."BOLDRED"%d\t"WHT, ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], network);
		network += obj.subnet[0x00];
		broadcast = network - 0x01;
		printf("  -\t%d.%d.%d."BOLDRED"%d\t"WHT"->[%d]\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], broadcast, numbers);
		numbers++;
	} while(network <=0xff);
	LINE
}

void prefix16_23(ipaddr *ip) {
	object obj;

	obj.grade[0x00] = 0x20 - ip->prefix;
	obj.grade[0x01] = 0x18 - ip->prefix;
	obj.subnet[0x00] = pow (2, obj.grade[0x00]);
	obj.subnet[0x01] = pow (2, obj.grade[0x01]);
	obj.mask = 0x100 - obj.subnet[0x01];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], ip->octet[0x03]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, 0xff, obj.mask, 0x00);
	host = obj.subnet[0x00] - 0x02;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d."BOLDRED"%d.%d\t"WHT, ip->octet[0x00], ip->octet[0x01], network, 0x00);
		network += obj.subnet[0x01];
		broadcast = network - 0x01;
		printf("  -\t%d.%d."BOLDRED"%d.%d\t"WHT"->[%d]\n", ip->octet[0x00], ip->octet[0x01], broadcast, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	LINE
}

void prefix8_15(ipaddr *ip) {
	object obj;

	obj.grade[0x00] = 0x20 - ip->prefix;
	obj.grade[0x01] = 0x10 - ip->prefix;
	obj.subnet[0x00] = pow (2, obj.grade[0x00]);
	obj.subnet[0x01] = pow (2, obj.grade[0x01]);
	obj.mask = 0x100 - obj.subnet[0x01];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], ip->octet[0x03]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, obj.mask, 0x00, 0x00);
	host = obj.subnet[0x00] - 0x02;
	printf("Host available: %d\n", host);

	LINE
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d."BOLDRED"%d.%d.%d\t"WHT, ip->octet[0x00], network, 0x00, 0x00);
		network += obj.subnet[0x01];
		broadcast = network - 0x01;
		printf(" -\t%d."BOLDRED"%d.%d.%d\t"WHT"->[%d]\n", ip->octet[0x00], broadcast, 0xff, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	LINE
}
