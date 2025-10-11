.PHONY: build clean all step0

all: build

build:
	@echo "Building all Qt Arkanoid projects..."
	mkdir -p build
	cd build && cmake .. && make

step0:
	@echo "Building step0 projects..."
	mkdir -p build
	cd build && cmake .. && make hello-world widgets-signals

hello-world: build
widgets-signals: build
arkanoid: build

clean:
	rm -rf build/
