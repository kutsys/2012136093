CC=gcc

tttt: ipc_producer3 ipc_consumer3

ipc_producer3: ipc_producer3.c
	$(CC) -o ipc_producer3 ipc_producer3.c -lpthread

ipc_consumer3: ipc_consumer3.c
	$(CC) -o ipc_consumer3 ipc_consumer3.c -lpthread

.PHONY: update
update:
	touch ipc_producer3.c ipc_consumer3.c
