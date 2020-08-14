/*
** p4p1: https://leosmith.xyz/
** Created on: Fri 14 Aug 2020 06:10:38 AM CEST
** main.c
** File description:
** It's a trap!
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "trap.h"

static void usage(char *arg)
{
	printf("%s [-p PORT_NUMBER] [-h]\n"
		"IT'S A http TRAP\n"
		"Default port: 4040\n", arg);
}

static void loop(struct trap *trp)
{
	int tmps = 0;
	socklen_t addrlen = sizeof(trp->address);
	char buf[BUFSIZ];
	FILE *fp = NULL;

	fp = fopen("trap.log", "w+");
	while ((tmps = accept(trp->socket, (struct sockaddr *)&trp->address, &addrlen)) > 0) {
		read(tmps, buf, BUFSIZ);
		fprintf(fp, "%s\n", buf);
		fflush(fp);
		close(tmps);
	}
	fclose(fp);
	free(trp);
	fprintf(stderr, "Error: could not accept connection\n");
	exit(EXIT_FAILURE);
}

static int daemond(void) {
	pid_t	process_id = 0;
	pid_t	sid = 0;

	if ((process_id = fork()) < 0) {
		fprintf(stderr, "Error: fork\n");
		return (-1);
	}
	if (process_id > 0) {
		printf("process_id of child process %d\n", process_id);
		exit(EXIT_SUCCESS);
	}
	umask(0);
	if ((sid = setsid()) < 0) {
		fprintf(stderr, "Error: setsid\n");
		exit(EXIT_FAILURE);
	}
	chdir("/tmp");
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	return (0);
}

int main(int argc, char *argv[])
{
	char	ch = 0;
	struct trap	*trp = init_trap();

	if (trp == NULL)
		return (-1);
	while ((ch = getopt(argc, argv, "p:h")) != -1 ) {
		if (ch == 'h')
			usage(argv[0]);
		else if (ch == 'p')
			trp->port = atoi(optarg);
		else
			return (-1);
	}
	serv_set(trp);
	if (daemond() < 0)
		return (-1);
	loop(trp);
	free(trp);
	return (0);
}
