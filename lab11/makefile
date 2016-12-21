CC=gcc

tttt: ipc_producer2 ipc_consumer2

ipc_producer2: ipc_producer2.c
	$(CC) -o ipc_producer2 ipc_producer2.c -lpthread

ipc_consumer2: ipc_consumer2.c
	$(CC) -o ipc_consumer2 ipc_consumer2.c -lpthread

.PHONY: update
update:
	touch ipc_producer2.c ipc_consumer2.c

