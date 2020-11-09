#ifndef _SUBNET_H
#define _SUBNET_H

#define BOLDRED "\x1B[1m\033[31m"
#define WHT "\033[37m"
#define __DOT_ '.'
#define __PREFIX_ '/'
#define LONG_ARG_C "--classC"
#define SHORT_ARG_C "-cC"
#define LONG_ARG_B "--classB"
#define SHORT_ARG_B "-cB"
#define LONG_ARG_A "--classA"
#define SHORT_ARG_A "-cA"
#define LINE puts("=============================================");

typedef struct __IPv4 {
	int octet[0x04];
	int prefix;
} ipaddr;

typedef struct __obj {
	int grade[0x02];
	int subnet[0x02];
	int mask;
} object;

void moveBuffer(char *buff, ipaddr *__IP_addrv4);
void prefix24_30(ipaddr *__IP_addrv4);
void prefix16_23(ipaddr *__IP_addrv4);
void prefix8_15(ipaddr *__IP_addrv4);

#endif
