.PHONY: build configure clean run

configure:
	cmake -S . -B build

build: configure
	cmake --build build

run: build
	./build/qt-arkanoid

clean:
	rm -rf build
