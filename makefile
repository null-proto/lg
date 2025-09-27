.PHONY: compile setup

CC = c++
CFLAG = $(shell pkg-config --cflags pam)
CLIBS = $(shell pkg-config --libs pam)


default: compile

setup:
	mkdir -p build/bin

compile:
	$(CC) $(CFLAG) $(CLIBS) src/main.cpp -o build/bin/lt
