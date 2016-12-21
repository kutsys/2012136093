CC=gcc

tttt: ipc_producer4 ipc_consumer4

ipc_producer4: ipc_producer4.c
	$(CC) -o ipc_producer4 ipc_producer4.c -lpthread

ipc_consumer4: ipc_consumer4.c
	$(CC) -o ipc_consumer4 ipc_consumer4.c -lpthread

.PHONY: update
update:
	touch ipc_producer4.c ipc_consumer4.c

