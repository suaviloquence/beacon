CC=gcc
CFLAGS=-Wall -Wpedantic

NETNS=vpn
INSTALL_DIR=/etc/openvpn/helpers

netns-exec-all: downgrade netns-exec

downgrade: netns-exec.c
	$(CC) $(CFLAGS) -DDOWNGRADE -o downgrade netns-exec.c

netns-exec: netns-exec.c
	$(CC) $(CFLAGS) -DSUID -DDOWNGRADE_PATH=\"$(INSTALL_DIR)/downgrade\" -DNETNS=\"$(NETNS)\" -o netns-exec netns-exec.c

install: downgrade netns-exec
	install -m 4733 netns-exec $(INSTALL_DIR)
	install -m 0700 downgrade $(INSTALL_DIR)

clean:
	rm downgrade netns-exec
