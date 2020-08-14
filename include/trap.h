/*
** p4p1: http://p4p1.github.io/
** Created on: Fri 14 Aug 2020 06:17:29 AM CEST
** trap.h
** File description:
** It's a trap header!
*/

#ifndef TRAP_H_
#define TRAP_H_

#include <netinet/in.h>

#define FILE_NAME "trap.log"
#define DEFAULT_DIR "/tmp"

enum verb { VERBOSE_OFF = 0,
			VERBOSE_ON = 1 };

struct trap {
	unsigned int	port;
	unsigned short	verbose;

	int				socket;
	struct sockaddr_in	address;

	char	*file;
	char	*dir;
};

struct trap *init_trap(void);
void serv_set(struct trap *tp);

#endif /* End of TRAP_H_ */
