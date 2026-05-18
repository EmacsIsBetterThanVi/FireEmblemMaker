CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

all: help

help:
	@echo "run make wayland or make x11"

%.o: %.c
	@gcc -c $(OPTS) $< -o $@

prog: $(OFILES) 
	@gcc $(OPTS) -o FireEmblemMaker *.o $(shell pkg-config --libs gtk4)

wayland: OPTS+=$(shell pkg-config --cflags gtk4-wayland)
wayland: prog

x11: OPTS+=$(shell pkg-config --cflags gtk4-x11)
x11: cfg prog

clean: 
	@rm -rf *.o FireEmblemMaker *~
