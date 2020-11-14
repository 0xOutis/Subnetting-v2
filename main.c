/*
 * Author  : Outis
 * Release : Sunday,08-11-2020
 * Tool    : Subnetting V2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subnet.h"


int main(int argc, char **argv) {

	if (argc < 0x3) {
		LOG_ERROR("Error, Example: %s [ipaddr/prefix] -[options]\n", argv[0x0]);
		help();
		return 0x1;
	}

	ipaddr_t *addr = (ipaddr_t*)malloc(sizeof(ipaddr_t));
	moveBuffer(argv[0x1], addr);
	
	if ((strcmp(argv[0x2], LONG_ARG_C) == 0x0) || (strcmp(argv[0x2], SHORT_ARG_C) == 0x0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else {
			LOG_ERROR("Error, Examples: %s [ipaddr/prefix] -[options]\n", argv[0x0]);
			help();
			free(addr);
			return 0x1;
		}
	} else if ((strcmp(argv[0x2], LONG_ARG_B) == 0x0) || (strcmp(argv[0x2], SHORT_ARG_B) == 0x0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16_23(addr);
		else {
			LOG_ERROR("Error, Example: %s [ipaddr/prefix] -[option]\n", argv[0x0]);
			help();
			free(addr);
			return 0x1;
		}
		
	} else if ((strcmp(argv[0x2], LONG_ARG_A) == 0x0) || (strcmp(argv[0x2], SHORT_ARG_A) == 0x0)){
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24_30(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16_23(addr);
		else if (addr->prefix <= 0x0f && addr->prefix >=0x08)
			prefix8_15(addr);
		else {
			LOG_ERROR("Error, Example: %s [ipaddr/prefix] -[option]\n", argv[0x0]);
			help();
			free(addr);
			return 0x1;
		}
	} else {
		LOG_ERROR("Error, Example: %s [ipaddr/prefix] -[option]\n", argv[0x0]);
		help();
	}

	free(addr);
	return 0x0;
}
