all: build

build:
	mkdir build -p
	cd build; cmake .. ; make

test: build
	cd build; ./socket_test

clean:
	rm -rf build

.PHONY: build clean

