CFILES = $(wildcard *.c)
OFILES = $(CFILES:.c=.o)

all: help

help:
	@echo "run make wayland or make x11"

%.o: %.c
	@gcc -c $(OPTS) $< -o $@

libwren:
	@make -C wren/projects/make/ wren

prog: $(OFILES) libwren
	@gcc $(OPTS) -o FireEmblemMaker *.o wren/lib/libwren.a $(shell pkg-config --libs gtk4) -lm 

wayland: OPTS+=$(shell pkg-config --cflags gtk4-wayland)
wayland: prog

x11: OPTS+=$(shell pkg-config --cflags gtk4-x11)
x11: prog

clean:
	@rm -rf *.o FireEmblemMaker *~
	@make -C wren/projects/make/ clean
