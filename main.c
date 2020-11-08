#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "subnet.h"


int main(int argc, char **argv) {

	if (argc < 0x03) {
		printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0x00]);
		error();
		return EXIT_FAILURE;
	}

	char address[0x1c];
	strcpy(address, argv[0x01]);
	char *tmp = (char*)malloc(0x03*sizeof(char));
	ipaddr *addr = (ipaddr*)malloc(sizeof(ipaddr));
	int y=0, x=0;

	for (int i=0;i<strlen(address);i++) {
		if ((address[i] != '.') && (address[i] != '/')) {
			tmp[x] = address[i];
			x++;
		}
		else if ((address[i] == '.') || (address[i] == '/')) {
			addr->octet[y] = atoi(tmp);
			memset(tmp,0x00,sizeof(tmp));
			x=0;
			y++;
			if (address[i] == '/') {
				for (int j=(i+0x01);j<=strlen(address);j++) {
					tmp[x] = address[j];
					x++;
				}
				addr->prefix = atoi(tmp);
				free(tmp);
				break;
			}
		}
	}

	if (strcmp(argv[0x02], "--classC") == 0) {
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0x00]);
			error();
			free(addr);
			return EXIT_FAILURE;
		}
	} else if (strcmp(argv[0x02], "--classB") == 0) {
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0x00]);
			error();
			free(addr);
			return EXIT_FAILURE;
		}
		
	} else if (strcmp(argv[0x02], "--classA") == 0) {
		if (addr->prefix <= 0x1e && addr->prefix >= 0x18)
			prefix24(addr);
		else if (addr->prefix <= 0x17 && addr->prefix >= 0x10)
			prefix16(addr);
		else if (addr->prefix <= 0x0f && addr->prefix >=0x08)
			prefix8(addr);
		else {
			printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
			error();
			free(addr);
			return EXIT_FAILURE;
		}
	} else {
		printf("Error, Example: %s [ip_addr]/[prefix] -[option]\n", argv[0]);
		error();
	}

	free(addr);
	return EXIT_SUCCESS;
}
