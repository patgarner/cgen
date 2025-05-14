export PKG_CONFIG_PATH=/usr/local/lib/pkgconfig
CC=gcc
CFLAGS=-I.

TARGET=cgen

all: $(TARGET)

$(TARGET): main_tmp.o
	$(CC) -o $@ $^ $(CFLAGS)
	rm -f main_tmp.c main_tmp.o main.c.txt Makefile.txt

main_tmp.o: main.c Makefile
	perl -pe 's/\\/\\\\/g; s/"/\\"/g; chomp; $$_="\"$$_\\n\""' Makefile > Makefile.txt
	perl -pe 's/\\/\\\\/g; s/"/\\"/g; chomp; $$_="\"$$_\\n\""'  main.c > main.c.txt
	cp main.c main_tmp.c
	perl -0777 -pe 'BEGIN { $$/=undef; $$t=`cat Makefile.txt`; $$s=`cat main.c.txt`; }  s/\"<source_code>\"/$$s/g; s/\"<makefile>\"/$$t/g;' main.c > main_tmp.c
	$(CC) -c -o $@ main_tmp.c $(CFLAGS)

run: $(TARGET)
	./$(TARGET)

install: $(TARGET)
	install ./$(TARGET) /usr/local/bin/

clean:
	rm -f *.o $(TARGET) main.c.txt Makefile.txt

.PHONY: all run install clean
