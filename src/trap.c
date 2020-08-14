/*
** p4p1: http://p4p1.github.io/
** Created on: Fri 14 Aug 2020 06:21:38 AM CEST
** trap.c
** File description:
** Definitions of trap structures
*/

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#include "config.h"

struct trap *init_trap(void)
{
	struct trap *tmp = malloc(sizeof(struct trap));
	int opt = 1;

	if (tmp == NULL)
		return (NULL);
	memset(tmp, 0, sizeof(struct trap));
	tmp->port = 4040;
	tmp->verbose = VERBOSE_OFF;
	tmp->socket = socket(AF_INET, SOCK_STREAM, 0);
	if (tmp->socket <= 0) {
		free(tmp);
		return (NULL);
	}
	if (setsockopt(tmp->socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
				&opt, sizeof(opt))) {
		free(tmp);
		fprintf(stderr, "Error: setsockopt error.\n");
		return (NULL);
	}
	if ((tmp->file = strdup(FILE_NAME)) == NULL) {
		free(tmp);
		return (NULL);
	}
	if ((tmp->dir = strdup(DEFAULT_DIR)) == NULL) {
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

void serv_set(struct trap *tp)
{
	tp->address.sin_family = AF_INET;
	tp->address.sin_addr.s_addr = INADDR_ANY;
	tp->address.sin_port = htons(tp->port);
	if (bind(tp->socket, (struct sockaddr *)&tp->address,
				sizeof(tp->address)) < 0) {
		free(tp);
		fprintf(stderr, "Error: bind error.\n");
		exit(EXIT_FAILURE);
	}
	if (listen(tp->socket, 3) < 0) {
		free(tp);
		fprintf(stderr, "Error: listen error.\n");
		exit(EXIT_FAILURE);
	}
	chdir(tp->dir);
}
