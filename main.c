/*
 * Author  : Outis
 * Release : Sunday,08-11-2020
 * Tool    : Subnetting V2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subnet.h"

void examples() {
	puts("Options: ");
	puts("\t# Long argument [--classC] or Short argument [-cC]");
	puts("\t\tPrefix: [24 - 30]");
	puts("\t# Long argument [--classB] or Short argument [-cB]");
	puts("\t\tPrefix: [16 - 23] [24 - 30]");
	puts("\t# Long argument [--classA] or Short argument [-cA]");
	puts("\t\tPrefix: [8 - 15] [16 - 23] [24 - 30]");
	puts("Examples:");
	puts("IP address Class C: ./subnet 192.168.10.1/24 --classC");
	puts("IP address Class B: ./subnet 172.16.10.22/16 --classB");
	puts("IP address Class A: ./subnet 10.10.1.1/8 --classA");
}

int main(int argc, char **argv) {

	if (argc < 3) {
		printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
		examples();
		return EXIT_FAILURE;
	}

	ipaddr *addr = (ipaddr*)malloc(sizeof(ipaddr));
	moveBuffer(argv[1], addr);

	if ((strcmp(argv[2], LONG_ARG_C) == 0) || (strcmp(argv[2], SHORT_ARG_C) == 0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
			examples();
			free(addr);
			return EXIT_FAILURE;
		}
	} else if ((strcmp(argv[2], LONG_ARG_B) == 0) || (strcmp(argv[2], SHORT_ARG_B) == 0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16_23(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0x00]);
			examples();
			free(addr);
			return EXIT_FAILURE;
		}
		
	} else if ((strcmp(argv[2], LONG_ARG_A) == 0) || (strcmp(argv[2], SHORT_ARG_A) == 0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16_23(addr);
		else if (addr->prefix <= 0x0f && addr->prefix >=0x08)
			prefix8_15(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
			examples();
			free(addr);
			return EXIT_FAILURE;
		}
	} else {
		printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
		examples();
	}

	free(addr);
	return EXIT_SUCCESS;
}
