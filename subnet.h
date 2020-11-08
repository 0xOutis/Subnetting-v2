#ifndef _SUBNET_H
#define _SUBNET_H

#define BOLDRED "\x1B[1m\033[31m"
#define WHT "\033[37m"

typedef struct __IPv4 {
	int octet[0x04];
	int prefix;
} ipaddr;

typedef struct __obj {
	int grade[0x02];
	int subnet[0x02];
	int mask;
} object;

void line();
void error();

void prefix24(ipaddr *__IP_addrv4);
void prefix16(ipaddr *__IP_addrv4);
void prefix8(ipaddr *__IP_addrv4);

#endif
