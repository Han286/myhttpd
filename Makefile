all: httpd client

httpd: server.cpp
	g++ -g -W -Wall -pthread -o $@ $<

client: client.c
	gcc -W -Wall -o $@ $<

clean:
	rm client httpd compile_commands.json

build:
	bear make all