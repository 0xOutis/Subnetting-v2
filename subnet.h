#ifndef _SUBNET_H
#define _SUBNET_H

#define BOLDRED "\x1B[1m\033[31m"
#define WHT "\033[37m"

/* Variadic macro */
#define LOG_ERROR(format, ...) \
	fprintf(stderr, format, __VA_ARGS__)

#define __DOT_ '.'
#define __PREFIX_ '/'
#define LONG_ARG_C "--classC"
#define SHORT_ARG_C "-cC"
#define LONG_ARG_B "--classB"
#define SHORT_ARG_B "-cB"
#define LONG_ARG_A "--classA"
#define SHORT_ARG_A "-cA"
#define LINE puts("=============================================");

typedef struct{
	int grade[0x2];
	int subnet[0x2];
	int mask;
} object_t;

typedef struct{
	int octet[0x4];
	int prefix;
	object_t object;
} ipaddr_t;

void help();

void moveBuffer(void *buff, ipaddr_t *__IP_addrv4);
void prefix24_30(ipaddr_t *__IP_addrv4);
void prefix16_23(ipaddr_t *__IP_addrv4);
void prefix8_15(ipaddr_t *__IP_addrv4);

#endif
