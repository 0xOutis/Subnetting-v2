#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "subnet.h"

int host;
int network=0,broadcast=0;
int numbers=1;

void line() {
	puts("=============================================");
}

void error() {
	puts("Options: ");
	puts("\t#--classC");
	puts("\t\tPrefix: 24 - 30");
	puts("\t#--classB");
	puts("\t\tPrefix: 16 - 23, 24 - 30");
	puts("\t#--classA");
	puts("\t\tPrefix: 8 - 15, 16 - 23, 24 - 30");
	puts("Examples:");
	puts("IP address Class C: ./subnet 192.168.10.1/24 --classC");
	puts("IP address Class B: ./subnet 172.16.10.22/16 --classB");
	puts("IP address Class A: ./subnet 10.10.1.1/8 --classA");
}

void prefix24(ipaddr *ip) {
	object obj;

	obj.grade[0x00] = 0x20 - ip->prefix;
	obj.subnet[0x00] = pow (2, obj.grade[0x00]);
	obj.mask = 0x100 - obj.subnet[0x00];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], ip->octet[0x03]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, 0xff, 0xff, obj.mask);
	host = obj.subnet[0x00] - 0x02;
	printf("Host available: %d\n", host);

	line();
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d.%d."BOLDRED"%d\t"WHT, ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], network);
		network += obj.subnet[0x00];
		broadcast = network - 0x01;
		printf("  -\t%d.%d.%d."BOLDRED"%d\t"WHT"->[%d]\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], broadcast, numbers);
		numbers++;
	} while(network <=0xff);
	line();
}

void prefix16(ipaddr *ip) {
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

	line();
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d.%d."BOLDRED"%d.%d\t"WHT, ip->octet[0x00], ip->octet[0x01], network, 0x00);
		network += obj.subnet[0x01];
		broadcast = network - 0x01;
		printf("  -\t%d.%d."BOLDRED"%d.%d\t"WHT"->[%d]\n", ip->octet[0x00], ip->octet[0x01], broadcast, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	line();
}

void prefix8(ipaddr *ip) {
	object obj;

	obj.grade[0x00] = 0x20 - ip->prefix;
	obj.grade[0x01] = 0x16 - ip->prefix;
	obj.subnet[0x00] = pow (2, obj.grade[0x00]);
	obj.subnet[0x01] = pow (2, obj.grade[0x01]);
	obj.mask = 0x100 - obj.subnet[0x01];

	printf("IP Address: %d.%d.%d.%d\n", ip->octet[0x00], ip->octet[0x01], ip->octet[0x02], ip->octet[0x03]);
	printf("Subnetmask: %d.%d.%d.%d\n", 0xff, obj.mask, 0x00, 0x00);
	host = obj.subnet[0x00] - 0x02;
	printf("Host available: %d\n", host);

	line();
	printf(" Network\t\t Broadcast\n");
	do {
		printf("%d."BOLDRED"%d.%d.%d\t"WHT, ip->octet[0x00], network, 0x00, 0x00);
		network += obj.subnet[0x01];
		broadcast = network - 0x01;
		printf(" -\t%d."BOLDRED"%d.%d.%d\t"WHT"->[%d]\n", ip->octet[0x00], broadcast, 0xff, 0xff, numbers);
		numbers++;
	} while(network <= 0xff);
	line();
}
