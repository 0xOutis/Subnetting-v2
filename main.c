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

	char address[0x1c];
	strcpy(address, argv[0x1]);
	char *tmp = (char*)malloc(0x3*sizeof(char));
	ipaddr_t *addr = (ipaddr_t*)malloc(sizeof(ipaddr_t));
	int y=0x0, x=0x0;

	for (int i=0x0;i<strlen(address);i++) {
		if ((address[i] != __DOT_) && (address[i] != __PREFIX_)) {
			tmp[x] = address[i];
			x++;
		}
		else if ((address[i] == __DOT_) || (address[i] == __PREFIX_)) {
			addr->octet[y] = atoi(tmp);
			memset(tmp,0x00,sizeof(&tmp));
			x=0x0;
			y++;
			if (address[i] == __PREFIX_) {
				for (int j=(i+0x1);j<=strlen(address);j++) {
					tmp[x] = address[j];
					x++;
				}
				addr->prefix = atoi(tmp);
				free(tmp);
				break;
			}
		}
	}

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
