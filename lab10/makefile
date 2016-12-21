CC=gcc

tttt: ipc_producer ipc_consumer

ipc_producer: ipc_producer.c
	$(CC) -o ipc_producer ipc_producer.c

ipc_consumer: ipc_consumer.c
	$(CC) -o ipc_consumer ipc_consumer.c

.PHONY: update
update:
	touch ipc_producer.c ipc_consumer.c
