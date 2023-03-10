#include <linux/if_ether.h>

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "ethertype.h"
#include "develop.h"
#include "tools.h"

int main(int argc, char argv[]) {
	int sock;
	struct sockaddr addr;
	// char buffer[1024];

	if ((sock = socket(PF_PACKET, SOCK_PACKET, htons(ETH_P_ALL))) < 0) {
		error("Failed to create socket!");
		exit(sock);
	}

	strcpy(addr.sa_data, "enp6s0");

	// debug("#%02x", CHAR(ETHER_TYPE_8021Q_CVID, 0));

	// memset(buffer, 0, sizeof(buffer));
	char buffer[512] = {
	// DSTMAC
	0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
	// SRCMAC
	0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
	// TYPEi <https://www.iana.org/assignments/ieee-802-numbers/ieee-802-numbers.xhtml>
	
	// CHAR(ETHER_TYPE_8021Q_CVID, 1), CHAR(ETHER_TYPE_8021Q_CVID, 0),
	// 0x00, 0x00,

	CHAR(ETHER_TYPE_IPV4, 1), CHAR(ETHER_TYPE_IPV4, 0),
	// IPv4, 
	// 0x0045,0x00,  0x01,0x50, 0x00,0x00, 0x00,0x00, 0x40,0x17,  0x00,0x00,
	0x0
	};

	sendto(sock, buffer, sizeof(buffer), 0, &addr, sizeof(addr));

	close(sock);
	
	return 0;
}
