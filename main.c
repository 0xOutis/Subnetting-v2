/*
 * Author  : Outis
 * Release : Sunday,08-11-2020
 * Tool    : Subnetting V2
*/

#include <stdio.h>
#include <stdlib.h>
#include "subnet.h" /* The header file contains */
		    /* the subnetting function declaration */

int main(int argc, char **argv) {

	if (argc < 2 || argc > 2) {
		note:	
		LOG_ERROR("Error, Example: %s [ipaddr/prefix]\n\n"
			  "Note:\n"
			  "\tRange ip class C = 192.0.0.0 to 223.255.255.0\n"
			  "\tRange ip class B = 128.0.0.0 to 191.255.0.0\n"
			  "\tRange ip class A = 1.0.0.0 to 126.0.0.0\n\n"
			  "Prefix:\n"
			  "\tIp class C = 24-30\n"
			  "\tIp class B = 16-30\n"
			  "\tIp class A = 8-30\n\n"
			  "Examples:\n"
			  "\tFor class C = %s 192.168.10.1/24\n"
			  "\tFor class B = %s 172.16.10.22/18\n"
		          "\tFor class A = %s 10.10.1.1/12\n", 
			  argv[0], argv[0], argv[0], argv[0]);
		return 0x1;
	}

	ipaddr_t *addr = (ipaddr_t*)malloc(sizeof(ipaddr_t));
	moveBuffer(argv[1], addr);
	
	/* for Prefix range 24-30 */
	if ((addr->prefix <= 0x1e) && (addr->prefix >= 0x18))
		RANGE24(addr);
	/* for Prefix range 16-23 */	
	else if ((addr->prefix <= 0x17) && (addr->prefix >= 0x10))
		RANGE16(addr);
	/* for Prefix range 8-15 */
	else if ((addr->prefix <= 0x0f) && (addr->prefix >= 0x08))
		RANGE8(addr);
	else
		goto note;

	free(addr);
	return 0x0;
}
