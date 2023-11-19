#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#ifdef SUID

#ifdef DOWNGRADE
#error "Please only define SUID or DOWNGRADE"
#endif // ifdef DOWNGRADE
			 
#ifndef DOWNGRADE_PATH
#error "Please specify DOWNGRADE_PATH"
#endif // ifndef DOWNGRADE_PATH

#ifndef NETNS
#error "Please specify NETNS"
#endif // ifndef NETNS

#else // ifdef SUID

#ifndef DOWNGRADE
#error "No mode specified."
#endif // ifndef DOWNGRADE

#endif // ifdef SUID

int main(int argc, char *argv[]) {
#ifdef SUID
	// 5 (/sbin/ip netns exec NETNS DOWNGRADE_PATH) + 1 (real uid) + 1 (terminating NULL)
	int args_len = argc + 5 + 1 + 1;
	char **arguments = (char **) malloc(sizeof(char *) * args_len), **ptr = arguments;
	char uid[128];
	sprintf(uid, "%d", getuid());
	*ptr++ = "/sbin/ip";
	*ptr++ = "netns";
	*ptr++ = "exec";
	*ptr++ = NETNS;
	*ptr++ = DOWNGRADE_PATH;
	*ptr++ = uid;
	for (int i = 1; i < argc ; i++) *ptr++ = argv[i];
	*ptr = NULL;

	execv("/sbin/ip", arguments);
#endif // ifdef SUID
#ifdef DOWNGRADE
	int uid;
	if (argc < 3) {
		fprintf(stderr, "Not enough arguments provided!\n");
		return 1;
	}
	uid = atoi(argv[1]);
	if (uid < 1) {
		fprintf(stderr, "Invalid uid '%s'\n", argv[1]);
		return 1;
	}
	setuid(uid);

	// - 2 (argv[0..=1]) + 1 (terminating NULL)
	int arg_len = argc - 2 + 1;
	char **arguments = (char **) malloc(sizeof(char *) * (arg_len)), **ptr = arguments;
	for (int i = 2; i < argc; i++) *ptr++ = argv[i];
	*ptr = NULL;
	execv(argv[2], arguments);
#endif // ifdef DOWNGRADE
	fprintf(stderr, "execv() returned - this is not good.  errno is %d.\n", errno);
	perror("perror says");

	return 1;
}
