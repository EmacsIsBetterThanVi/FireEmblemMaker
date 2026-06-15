all: libwren liballegro FireEmblemMaker

full: libwren liballegro FireEmblemMaker

CFILES = $(wildcard *.c)
CFILES += $(wildcard wrenFireEmblem/*.c)
OFILES = $(CFILES:.c=.o)
COPTS = -I. -Iallegro5/include/ -Iallegro5/build/include -Iallegro5/addons/audio -Iallegro5/addons/image -Iallegro5/addons/font

targets:
	@echo "targets:"
	@echo "  build:"
	@echo "    liballegro      - Configure and build allegro"
	@echo "    libwren         - Configure and build wren"
	@echo "    FireEmblemMaker - Build the game, not including dependencies"
	@echo "    all, full       - Builds the game, including dependencies"
	@echo "    install         - Builds (including dependencies) and installs FireEmblemMaker"
	@echo "  clean:"
	@echo "    cleanAllegro    - Cleans the allegro build directory"
	@echo "    clean           - Cleans wren and FireEmblemMaker of build files"
	@echo "    cleanAll        - Cleans everything"
	@echo "  misc:"
	@echo "    targets         - Displays this message"
	@echo "    deps            - Lists all dependencies"

deps:
	@echo "Dependencies: allegro5(Provided), wren(Provided), libc, cmake 3.0(Build), libopengl, libx11, libpng, zlib, libogg, libvorbis, libvorbisfile"

%.o: %.c %.h
	@gcc $(COPTS) -c $< -o $@

allegro5/build:
	@mkdir allegro5/build

liballegro: allegro5/build
	@cmake -B allegro5/build -S allegro5
	@make -C allegro5/build allegro allegro_audio allegro_font allegro_image

win/liballegro: allegro5/build
	@cmake -B allegro5/build -S allegro5 -DCMAKE_TOOLCHAIN_FILE=$(PWD)/Windows.cmake
	@make -C allegro5/build

libwren:
	@make -C wren/projects/make/ wren

FireEmblemMaker: $(OFILES)
	@gcc -o FireEmblemMaker $(OFILES) wren/lib/libwren.a -lm -L./allegro5/build/lib -lallegro -lallegro_font -lallegro_image -lallegro_audio -Wl,-rpath,$(PWD)/allegro5/build/lib,-rpath,$(HOME)/.emacsisbetterthanvi/FEMaker/lib,-rpath,/usr/local/lib

test: FireEmblemMaker
	./FireEmblemMaker

cleanAllegro:
	@rm -rf allegro5/build

clean: # Clean does not clean the allegro build director, use cleanAllegro for that
	@rm -rf *.o FireEmblemMaker *~
	@make -C wren/projects/make/ clean

cleanAll: clean cleanAllegro

install: libwren liballegro FireEmblemMaker
ifneq ($(shell id -u), 0)
	@mkdir -p ~/.emacsisbetterthanvi/FEMaker
	@cp -rf assets ~/.emacsisbetterthanvi/FEMaker/
	@cmake -S allegro5/build -DCMAKE_INSTALL_PREFIX=$(HOME)/.emacsisbetterthanvi/FEMaker -P allegro5/build/cmake_install.cmake
else
	@cp FireEmblemMaker /bin/
	@mkdir /usr/share/FEMaker
	@cp -rf assets /usr/share/FEMaker
	@cmake -S allegro5/build -P allegro5/build/cmake_install.cmake
endif
