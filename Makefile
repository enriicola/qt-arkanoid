.PHONY: arkanoid hello-world widgets-signals clean all run

arkanoid:
	@echo "Building Arkanoid game..."
	@echo "Note: Main Arkanoid game not implemented yet ..."
	mkdir -p build

hello-world:
	@echo "Building Hello World..."
	mkdir -p build-hello-world
	cd build-hello-world && cmake ../hello-world && make

widgets-signals:
	@echo "Building Widgets + Signals/Slots Demo..."
	mkdir -p build-widgets-signals
	cd build-widgets-signals && cmake ../widgets-signals && make

clean:
	rm -rf build*/

all: arkanoid hello-world widgets-signals

%:
	@:
