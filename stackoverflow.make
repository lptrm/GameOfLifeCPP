.PHONY: all clean

all: glewinfo visualinfo

glewinfo: src/glewinfo.o
	gcc -O2 -Wall -W -Iinclude -o bin/glewinfo.exe src/glewinfo.o -Llib -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

visualinfo: src/visualinfo.o
	gcc -O2 -Wall -W -Iinclude -o bin/visualinfo.exe src/visualinfo.o -Llib -lglew32 -L/mingw/lib -lglu32 -lopengl32 -lgdi32 -luser32 -lkernel32

src/glewinfo.o: src/glewinfo.c
	gcc -c -O2 -Wall -W -Iinclude -o src/glewinfo.o src/glewinfo.c

src/visualinfo.o: src/visualinfo.c
	gcc -c -O2 -Wall -W -Iinclude -o src/visualinfo.o src/visualinfo.c

clean:
	rm -f src/*.o
	rm -f bin/glewinfo.exe
	rm -f bin/visualinfo.exe
