all: httpd client

httpd: server.c
	gcc -g -W -Wall -pthread -o $@ $<

client: client.c
	gcc -W -Wall -o $@ $<

clean:
	rm client httpd compile_commands.json

build:
	bear make all