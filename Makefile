.PHONY: all clean

all:
	make -C lib/
	make -C src/
	
clean:
	make clean -C lib/
	make clean -C src/
