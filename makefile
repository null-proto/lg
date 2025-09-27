.PHONY: compile setup

CC = c++


default: compile

setup:
	mkdir -p build/bin

compile:
	$(CC) src/main.cpp -o build/bin/lt
