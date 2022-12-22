all: build server client

build:
	mkdir build

server: src/server.cpp
	g++ src/server.cpp -o build/server

client: src/client.cpp
	g++ src/client.cpp -o build/client