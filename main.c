/*
 * Author  : Outis
 * Release : Sunday,08-11-2020
 * Tool    : Subnetting V2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subnet.h" /* The header file contains */
		    /* the subnetting function declaration */

int main(int argc, char **argv) {

	if (argc < 3) {
		LOG_ERROR("Error, Example: %s [ipaddr/prefix] [options]\n", argv[0]);
		help();
		return 0x1;
	}

	ipaddr_t *addr = (ipaddr_t*)malloc(sizeof(ipaddr_t));
	moveBuffer(argv[1], addr); /* Move argv[1] to struct ipaddr_t*/
	
	/* IP class C */
	if ((strcmp(argv[2], LONG_ARG_C) == 0) || (strcmp(argv[2], SHORT_ARG_C) == 0)){
		/* for Prefix range 24-30 */
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			RANGE_CLASS_C_24(addr);
		else {
			LOG_ERROR("Error, Examples: %s [ipaddr/prefix] [options]\n", argv[0]);
			help();
			free(addr);
			return 0x1;
		}
	/* IP class B */
	} else if ((strcmp(argv[2], LONG_ARG_B) == 0) || (strcmp(argv[2], SHORT_ARG_B) == 0)){
		/* for Prefix range 24-30 */
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			RANGE_CLASS_B_24(addr);
	        /* for Prefix range 16-23 */	
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			RANGE_CLASS_B_16(addr);
		else {
			LOG_ERROR("Error, Example: %s [ipaddr/prefix] [option]\n", argv[0]);
			help();
			free(addr);
			return 0x1;
		}
	/* IP class A */	
	} else if ((strcmp(argv[2], LONG_ARG_A) == 0) || (strcmp(argv[2], SHORT_ARG_A) == 0)){
		/* for Prefix range 24-30 */
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			RANGE_CLASS_A_24(addr);
		/* for Prefix range 16-23 */
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			RANGE_CLASS_A_16(addr);
		/* for Prefix range 8-15 */
		else if (addr->prefix <= 0x0f && addr->prefix >= 0x08)
			RANGE_CLASS_A_8(addr);
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
