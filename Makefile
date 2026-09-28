all: libwren liballegro FireEmblemMaker

full: libwren liballegro FireEmblemMaker

CFILES = $(wildcard *.c)
CFILES += $(wildcard wrenFireEmblem/*.c)
OFILES = $(CFILES:.c=.o)
COPTS = -I. -Iallegro5/include/ -Iallegro5/build/include -Iallegro5/addons/audio -Iallegro5/addons/image -Iallegro5/addons/font -Iallegro5/addons/ttf

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
	@echo "    clean           - Cleans FireEmblemMaker of build files"
	@echo "    cleanWren       - Cleans the wren build directory"
	@echo "    cleanRemote     - Cleans the remote assets directory"
	@echo "    cleanAll        - Cleans everything"
	@echo "  misc:"
	@echo "    targets         - Displays this message"
	@echo "    deps            - Lists all dependencies"
	@echo "    font            - Fetches font dependencies"

assets/engine/remote/:
	@mkdir assets/engine/remote

assets/engine/remote/font.ttf: assets/engine/remote/
	@wget https://ftp.gnu.org/gnu/freefont/freefont-ttf-20100919.tar.gz
	@tar -xf freefont-ttf-20100919.tar.gz freefont-20100919/FreeSerif.ttf -O > assets/engine/remote/font.ttf
	@rm -f freefont-ttf-20100919.tar.gz

font: assets/engine/remote/font.ttf

deps:
	@echo "Dependencies: allegro5(Provided), wren(Provided), libc, cmake 3.0(Build), libopengl, libx11, libpng, zlib, libogg, libvorbis, libvorbisfile"

%.o: %.c %.h
	@gcc $(COPTS) -c $< -o $@

allegro5/build:
	@mkdir allegro5/build

liballegro: allegro5/build
	@cmake -B allegro5/build -S allegro5
	@make -C allegro5/build allegro allegro_audio allegro_font allegro_image allegro_ttf

win/liballegro: allegro5/build
	@cmake -B allegro5/build -S allegro5 -DCMAKE_TOOLCHAIN_FILE=$(PWD)/Windows.cmake
	@make -C allegro5/build

libwren:
	@make -C wren/projects/make/ wren

FireEmblemMaker: font $(OFILES)
	@gcc -o FireEmblemMaker $(OFILES) wren/lib/libwren.a -lm -L./allegro5/build/lib -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -Wl,-rpath,$(PWD)/allegro5/build/lib,-rpath,$(HOME)/.emacsisbetterthanvi/FEMaker/lib,-rpath,/usr/local/lib

test: COPTS += -g
test: FireEmblemMaker
	@gdb -ex run FireEmblemMaker

cleanAllegro:
	@rm -rf allegro5/build

clean: # Clean does not clean the allegro build director, use cleanAllegro for that
	@rm -rf *.o wrenFireEmblem/*.o FireEmblemMaker *~

cleanWren:
	@make -C wren/projects/make/ clean

cleanRemote:
	@rm -rf assets/engine/remote

cleanAll: clean cleanWren cleanAllegro cleanRemote

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
