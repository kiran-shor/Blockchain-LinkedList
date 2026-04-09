all:
	g++ src/main.cpp -o blockchain -lssl -lcrypto

run: all
	./blockchain
