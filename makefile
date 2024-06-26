run_server: compile_server
	-@./server.o

compile_server:
	-@gcc ./server.c -o ./server.o

run_client: compile_client
	-@./client.o

compile_client:
	-@gcc ./client.c -o ./client.o