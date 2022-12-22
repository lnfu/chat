all: build server client

build:
	mkdir build

server: src/server*.cpp src/utility.cpp
	g++ src/server*.cpp src/utility.cpp -o build/server

client: src/client.cpp src/utility.cpp
	g++ src/client.cpp src/utility.cpp -o build/client