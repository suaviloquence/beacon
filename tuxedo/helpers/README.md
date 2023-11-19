# helpers

## netns-exec

uses a suid bit to execute in the correct namespace

### installation

1. edit the Makefile to the desired `NETNS` name (default: `vpn`) and the directory `INSTALL_DIR` where you want these executables

2. `make netns-exec-all`
3. `sudo make install`

### usage

take note of your `INSTALL_DIR`, then run `$INSTALL_DIR/netns-exec /path/to/command args`

- IMPORTANT: it does not check `$PATH` so you need the qualified path to the executable, not just the command like you would put into the shell  


### notes

- be wary of anything that uses suid, there is always a chance of security flaws
- this includes the `downgrade` utility that uses `setuid` to run a command as a passed user id, like `sudo -u`
 - if you want to use this on its own for some reason (bad idea), you can do `$INSTALL_DIR/downgrade $UID /path/to/command args`
 - like `netns-exec`, this needs the qualified path to the executable, no `$PATH`
