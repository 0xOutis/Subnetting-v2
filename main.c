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

	if (argc < 3) {
		LOG_ERROR("Error, Example: %s [ipaddr/prefix] [options]\n", argv[0]);
		help();
		return 0x1;
	}

	ipaddr_t *addr = (ipaddr_t*)malloc(sizeof(ipaddr_t));
	moveBuffer(argv[1], addr);
	
	if ((strcmp(argv[2], LONG_ARG_C) == 0) || (strcmp(argv[2], SHORT_ARG_C) == 0)){
		if (addr->prefix <= 30 && addr->prefix >= 24)
			prefix24_30(addr);
		else {
			LOG_ERROR("Error, Examples: %s [ipaddr/prefix] [options]\n", argv[0]);
			help();
			free(addr);
			return 0x1;
		}
	} else if ((strcmp(argv[2], LONG_ARG_B) == 0) || (strcmp(argv[2], SHORT_ARG_B) == 0)){
		if (addr->prefix <= 30 && addr->prefix >= 24)
			prefix24_30(addr);
		else if (addr->prefix <= 23 && addr->prefix >= 16)
			prefix16_23(addr);
		else {
			LOG_ERROR("Error, Example: %s [ipaddr/prefix] [option]\n", argv[0]);
			help();
			free(addr);
			return 0x1;
		}
		
	} else if ((strcmp(argv[2], LONG_ARG_A) == 0) || (strcmp(argv[2], SHORT_ARG_A) == 0)){
		if (addr->prefix <= 30 && addr->prefix >= 24)
			prefix24_30(addr);
		else if (addr->prefix <= 23 && addr->prefix >= 16)
			prefix16_23(addr);
		else if (addr->prefix <= 15 && addr->prefix >= 8)
			prefix8_15(addr);
		else {
			LOG_ERROR("Error, Example: %s [ipaddr/prefix] [option]\n", argv[0]);
			help();
			free(addr);
			return 0x1;
		}
	} else {
		LOG_ERROR("Error, Example: %s [ipaddr/prefix] [option]\n", argv[0]);
		help();
	}

	free(addr);
	return 0x0;
}
